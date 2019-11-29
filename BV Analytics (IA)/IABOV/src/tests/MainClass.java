package tests;

import java.io.IOException;
import constants.FileLocation;
import helper.CheckFile;

public class MainClass {
    
    public static void main(String[] args) {
        
        try {
            new CheckFile(FileLocation.LOCAL_OUTPUT, null).start();
            
            Runtime.getRuntime().exec("cmd /c start "+FileLocation.EXEC+
                                    " /k \"cd "+FileLocation.LOCAL_ARCHIVE+
                                    " && "+FileLocation.ARCHIVE_NAME+"\"");
        
        } catch (IOException e) {
            System.out.println("ERRO: "+e.getMessage());
        }
    }
}
