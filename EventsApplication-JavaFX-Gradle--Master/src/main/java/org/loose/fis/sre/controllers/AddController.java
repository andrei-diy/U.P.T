package org.loose.fis.sre.controllers;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.loose.fis.sre.model.Event;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

import java.io.IOException;

public class AddController {

    @FXML
    private Button save1;

    @FXML
    private TextField tdate;

    @FXML
    private TextField tname;

    @FXML
    private TextField tnot;

    @FXML
    private TextField tplace;

    public Event New;

    public void initialize(){
    }
    @FXML
    public void addEventt(ActionEvent event) throws IOException{

        New = new Event();
        if(!tname.getText().isEmpty()){ New.setName(tname.getText());}
        if(!tplace.getText().isEmpty()){ New.setPlace(tplace.getText());}
        if(!tdate.getText().isEmpty()){ New.setDate(tdate.getText());}
        if(!tnot.getText().isEmpty()){ New.setNOT(Integer.parseInt(tnot.getText()));}
        if (!New.isEmpty()){
            ManagerPageController.add = New;
        }

        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("ManagerPage.fxml"));
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Events App");
        stage.show();
    }

}
