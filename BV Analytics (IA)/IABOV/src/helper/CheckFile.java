package helper;

import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JTextArea;
import constants.FileLocation;
import java.io.BufferedReader;
import java.io.FileReader;

public class CheckFile extends Thread{
    
    private final String path;
    private final JTextArea txt;
    
    public CheckFile(String path, JTextArea txt){
        this.path = path;
        this.txt = txt;
    }
    
    @Override
    public void run(){
        File output = new File(path+"\\"+FileLocation.OUTPUT_NAME);
        while(true && !output.exists()){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(CheckFile.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        //ler arquivo quando estiver disponivel
        try {
            BufferedReader read = new BufferedReader(new FileReader(path+"\\"+FileLocation.OUTPUT_NAME));
            while(read.ready()){
                String linha = read.readLine();
                String text = txt.getText();
                txt.setText(text.concat(linha+"\n"));
            }
            read.close();
        } catch (Exception e) {
            System.out.println("Ocorreu um erro ao tentar abrir o arquivo.");
        }
    }
}
