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

public class EditController {

    @FXML
    private Button save;

    @FXML
    private TextField tdate;

    @FXML
    private TextField tname;

    @FXML
    private TextField tnot;

    @FXML
    private TextField tplace;

    public static Event buf;

    public void initialize(){
        buf = ManagerPageController.edit;
    }
    @FXML
    public void save(ActionEvent event) throws IOException {
         if(!tname.getText().isEmpty()){ buf.setName(tname.getText());}
         if(!tplace.getText().isEmpty()){ buf.setPlace(tplace.getText());}
         if(!tdate.getText().isEmpty()){ buf.setDate(tdate.getText());}
         if(!tnot.getText().isEmpty()){ buf.setNOT(Integer.parseInt(tnot.getText()));}
         ManagerPageController.edit = buf;

        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("ManagerPage.fxml"));
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Events App");
        stage.show();
    }


}
