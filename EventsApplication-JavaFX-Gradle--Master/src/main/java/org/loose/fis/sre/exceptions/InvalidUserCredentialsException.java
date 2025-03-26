package org.loose.fis.sre.exceptions;

public class InvalidUserCredentialsException extends Exception {

    private String username;
    public InvalidUserCredentialsException(String username) {
        super(String.format("Invalid Credentials, User: %s doesn't exists!", username));
        this.username = username;
    }

    public String getUsername() {
        return username;
    }
}

