package org.loose.fis.sre.services;

import org.dizitart.no2.Nitrite;
import org.dizitart.no2.objects.ObjectRepository;
import org.loose.fis.sre.exceptions.InvalidUserCredentialsException;
import org.loose.fis.sre.exceptions.UsernameAlreadyExistsException;
import org.loose.fis.sre.model.User;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Objects;

import static org.loose.fis.sre.services.FileSystemService.getPathToFile;

public class UserService {

    private static ObjectRepository<User> userRepository;
    public static User currentUser;
    public static void initDatabase() {
        Nitrite database = Nitrite.builder()
                .filePath(getPathToFile("Events_App.db").toFile())
                .openOrCreate("test", "test");

        userRepository = database.getRepository(User.class);
    }
    public static ObjectRepository<User> getDatabase(){
        return userRepository;
    }
    public static void addUser(String username, String password, String role) throws UsernameAlreadyExistsException {
        checkUserDoesNotAlreadyExist(username);
        userRepository.insert(new User(username, encodePassword(username, password), role));
    }
    private static String encodePassword(String salt, String password) {
        MessageDigest md = getMessageDigest();
        md.update(salt.getBytes(StandardCharsets.UTF_8));

        byte[] hashedPassword = md.digest(password.getBytes(StandardCharsets.UTF_8));

        // This is the way a password should be encoded when checking the credentials
        return new String(hashedPassword, StandardCharsets.UTF_8)
                .replace("\"", ""); //to be able to save in JSON format
    }

    public static void checkAccount(String username,String password) throws InvalidUserCredentialsException{
        int ok=0;
        for (User user : userRepository.find()) {
            if (Objects.equals(username, user.getUsername()) && Objects.equals(encodePassword(username, password),user.getPassword()))
            {   ok=1;
                currentUser = user;}
        }
        if(ok==0) throw new InvalidUserCredentialsException(username);
    }

    public static String checkRole(String username){
        for (User user : userRepository.find()) {
            if (Objects.equals(username, user.getUsername()))
                return user.getRole();
        }
        return "";
    }

    private static void checkUserDoesNotAlreadyExist(String username) throws UsernameAlreadyExistsException {
        for (User user : userRepository.find()) {
            if (Objects.equals(username, user.getUsername()))
                throw new UsernameAlreadyExistsException(username);
        }
    }
    private static MessageDigest getMessageDigest() {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("SHA-512");
        } catch (NoSuchAlgorithmException e) {
            throw new IllegalStateException("SHA-512 does not exist!");
        }
        return md;
    }


}
