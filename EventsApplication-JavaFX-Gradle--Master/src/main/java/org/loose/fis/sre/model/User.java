package org.loose.fis.sre.model;

import org.dizitart.no2.objects.Id;

public class User {
    @Id
    private String username;
    private String password;
    private String role;
    public Event [] events = new Event[20];
    private int contor=0;

    public User(String username, String password, String role) {
        this.username = username;
        this.password = password;
        this.role = role;
        contor = 0;
    }

    public User() {
        contor = 0;
    }

    public User(User aux) {
        this.username = aux.getUsername();
        this.password = aux.getPassword();
        this.role = aux.getRole();
        this.contor = aux.getContor();
        this.events = aux.events;
    }

    public void setEvents(Event[] ev){
        this.events = ev;
    }

    public Event[] getEvents() {
        if (contor==0) {
            return null;
        }else{
            return events;
        }
    }
    public void addEvent(Event e){
        events[this.contor] = e;
        this.contor++;
    }
    public int getContor() {
        return contor;
    }

    public void setContor(int contor) {
        this.contor=contor;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        User user = (User) o;

        if (username != null ? !username.equals(user.username) : user.username != null) return false;
        if (password != null ? !password.equals(user.password) : user.password != null) return false;
        return role != null ? role.equals(user.role) : user.role == null;
    }

    @Override
    public int hashCode() {
        int result = username != null ? username.hashCode() : 0;
        result = 31 * result + (password != null ? password.hashCode() : 0);
        result = 31 * result + (role != null ? role.hashCode() : 0);
        return result;
    }
}
