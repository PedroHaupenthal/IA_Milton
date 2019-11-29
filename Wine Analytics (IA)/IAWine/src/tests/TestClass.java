
package tests;

import constants.FileLocation;
import java.io.IOException;

/**
 *
 * @author: Pedro Afonso Ferreira Haupenthal
 * Email: pedro.haupenthal@gmail.com
 */
public class TestClass {
    public static void main(String[] args) {
        
        try {
            Runtime.getRuntime().exec("cmd /c start "+FileLocation.EXEC+
                                    " /k \"cd "+FileLocation.LOCAL_ARCHIVE+
                                    " && "+FileLocation.ARCHIVE_NAME_RED+"\"");
        
        } catch (IOException e) {
            System.out.println("ERRO: "+e.getMessage());
        }
    }
}
