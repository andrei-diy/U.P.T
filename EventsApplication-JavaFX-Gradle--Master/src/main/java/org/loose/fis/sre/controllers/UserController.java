package org.loose.fis.sre.controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.shape.Line;
import javafx.stage.Stage;
import org.dizitart.no2.objects.ObjectRepository;
import org.loose.fis.sre.model.Event;
import org.loose.fis.sre.model.User;
import org.loose.fis.sre.services.UserService;

import java.io.IOException;
import java.util.Arrays;

public class UserController {
    @FXML
    private TextField searchtxt;
    @FXML
    private Line l1;
    @FXML
    private Line l2;
    @FXML
    private Line l3;
    @FXML
    private Line l4;
    @FXML
    private Label select;
    @FXML
    private Label namelbl;
    @FXML
    private TableView<Event> Tabel;
    @FXML
    private TableColumn<Event, String> Data;
    @FXML
    private TableColumn<Event, Integer> NOT;
    @FXML
    private TableColumn<Event, String> Name;
    @FXML
    private TableColumn<Event, String> Place;
    @FXML
    private ListView<String> listView = new ListView<String>();

    private static ObjectRepository<User> repository = UserService.getDatabase();

    private User U = UserService.currentUser;

    @FXML
    public void initialize(){
        Tabel.setVisible(false);
        listView.setVisible(false);
        l1.setVisible(false);l2.setVisible(false);l3.setVisible(false);l4.setVisible(false);
        Name.setCellValueFactory(new PropertyValueFactory<Event, String>("name"));
        Place.setCellValueFactory(new PropertyValueFactory<Event, String>("loc"));
        Data.setCellValueFactory(new PropertyValueFactory<Event, String>("data"));
        NOT.setCellValueFactory(new PropertyValueFactory<Event, Integer>("nrTickets"));
        namelbl.setText(UserService.currentUser.getUsername());
    }
    public void SearchEvents(){
        listView.setVisible(false);
        ObservableList<Event> records= FXCollections.observableArrayList();
        for(User user : repository.find()){
            if("Manager".equals(user.getRole())){
            if(user.getEvents()!=null){
                Event[] events = user.getEvents();
                int contor = user.getContor();
                records.addAll(Arrays.asList(events).subList(0, contor));
            }
          }
        }
        Tabel.setItems(records);
        Tabel.setVisible(true);
        l1.setVisible(true);l2.setVisible(true);l3.setVisible(true);l4.setVisible(true);

    }
    @FXML
    public void getSelection(){

        Event ev = Tabel.getSelectionModel().getSelectedItem();
        if(ev == null) return;
        String txt = "Selected: " + ev.toString();
        select.setText(txt);
    }
    public void MakeReservation(){

        Event ev = Tabel.getSelectionModel().getSelectedItem();
        if(ev == null) return;
        User buf = new User();

        buf.setUsername(U.getUsername());
        buf.setRole(U.getRole());
        buf.setPassword(U.getPassword());

        if(U.getEvents()!=null){
            buf.setEvents(U.getEvents());
            buf.setContor(U.getContor());
            buf.addEvent(ev);
        }else{buf.addEvent(ev);}

        repository.remove(U);
        repository.insert(buf);
        U=buf;
        UserService.currentUser = U;
    }
    public void History(){
        listView.getItems().clear();
        if(!listView.isVisible()){
            Tabel.setVisible(false);
            listView.setVisible(true);
            l1.setVisible(false);l2.setVisible(false);l3.setVisible(false);l4.setVisible(false);
        }
        listView.setVisible(true);
        int index = 1;
        for(int i=0; i<U.getContor();i++,index++){
            String txt = "  < "+ index + " >" + U.events[i].toString();
            listView.getItems().add(txt);
        }
    }
    public void searchName(){

        String find = searchtxt.getText();

        Tabel.getItems().stream()
                .filter(item -> find.equals(item.getName()))
                .findAny()
                .ifPresent(item -> {
                    Tabel.getSelectionModel().select(item);
                    Tabel.scrollTo(item);
                });
    }
    @FXML
    public void Logoff(ActionEvent a) throws IOException {
        Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("Login.fxml"));
        Stage stage = (Stage) ((Node) a.getSource()).getScene().getWindow();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Events App");
        stage.show();
    }
}