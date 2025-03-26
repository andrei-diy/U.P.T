package org.loose.fis.sre.controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import javafx.scene.control.Button;

import java.io.IOException;


public class StartPageController {

    public void openRegisterForm(javafx.event.ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("register.fxml"));
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Events App");
        stage.show();
    }
    public void openLoginForm(javafx.event.ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("Login.fxml"));
        Stage stage2 = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        Scene scene2 = new Scene(root);
        stage2.setScene(scene2);
        stage2.setTitle("Events App");
        stage2.show();
    }
}
