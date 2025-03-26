package org.loose.fis.sre.controllers;

//import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.loose.fis.sre.exceptions.InvalidUserCredentialsException;
import org.loose.fis.sre.model.User;
import org.loose.fis.sre.services.UserService;

import java.io.IOException;

public class LoginController {

    @FXML
    private Label loginMsg;
    @FXML
    private TextField usernameTxt;
    @FXML
    private PasswordField passwordTxt;
    private Stage stage;
    public void openRegisterForm(javafx.event.ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("register.fxml"));
        stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Events App");
        stage.show();
    }
    public void openUserMainPage(javafx.event.ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("UserPage.fxml"));
        stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        Scene scene2 = new Scene(root);
        stage.setScene(scene2);
        stage.setTitle("Events App");
        stage.show();
    }
    public void openManagerMainPage(javafx.event.ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("ManagerPage.fxml"));
        stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        Scene scene3 = new Scene(root);
        stage.setScene(scene3);
        stage.setTitle("Events App");
        stage.show();
    }

    public void LoginAction(javafx.event.ActionEvent actionEvent) throws IOException {
        try{
            UserService.checkAccount(usernameTxt.getText(),passwordTxt.getText());
            if ("User".equals(UserService.checkRole(usernameTxt.getText()))) {
                openUserMainPage(actionEvent);
            }
            else openManagerMainPage(actionEvent);
        }catch(InvalidUserCredentialsException e){
            loginMsg.setText(e.getMessage());
        }
    }
}
