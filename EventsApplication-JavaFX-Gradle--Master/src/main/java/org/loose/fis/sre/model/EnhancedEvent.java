package org.loose.fis.sre.model;

public class EnhancedEvent extends Event{
    private String user;
    public EnhancedEvent(){
        super();
    }
    public EnhancedEvent(Event ev, String User){
        super();
        this.user =user;
    }
    @Override
    public String toString(){
        return user + " --->  " + this.getName() + "    |    " + this.getLoc() + "    |    " + this.getData();
    }

}
