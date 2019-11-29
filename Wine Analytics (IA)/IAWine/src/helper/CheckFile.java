package helper;

import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;
import constants.FileLocation;
import java.awt.Color;
import java.io.BufferedReader;
import java.io.FileReader;
import javax.swing.JLabel;
import javax.swing.JProgressBar;

/**
 *
 * @author: Pedro Afonso Ferreira Haupenthal
 * Email: pedro.haupenthal@gmail.com
 */

public class CheckFile extends Thread{
    
    private final JLabel lblStatus;
    private final JProgressBar ProgressBar;
    private final JLabel lblQualidadeVinho;

    public CheckFile(JLabel lblStatus, JProgressBar ProgressBar, JLabel lblQualidadeVinho) {
        this.lblStatus = lblStatus;
        this.ProgressBar = ProgressBar;
        this.lblQualidadeVinho = lblQualidadeVinho;
    }
    
    @Override
    public void run(){
        //aguarda o arquivo quality.txt aparecer
        File output = new File(FileLocation.LOCAL_OUTPUTS+"\\"+FileLocation.OUTPUT_QLT);
        while(true && !output.exists()){
            try {
                lblStatus.setText("Processando...");
                lblStatus.setForeground(Color.red);
                ProgressBar.setIndeterminate(true);
                
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(CheckFile.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        //arquivo disponivel
        lblStatus.setText("Finalizado");
        lblStatus.setForeground(Color.green);
        ProgressBar.setIndeterminate(false);
        
        //ler arquivo
        try {
            String linha = "";
            
            BufferedReader read = new BufferedReader(new FileReader(FileLocation.LOCAL_OUTPUTS+"\\"+FileLocation.OUTPUT_QLT));
            
            linha = read.readLine();
            read.close();
            
            float quality = Float.parseFloat(linha);
            
            if(quality < 6 && quality >= 0){
                lblQualidadeVinho.setText("Baixa qualidade");
                lblQualidadeVinho.setForeground(Color.red);
            }
            else if(quality >= 6 && quality >= 0){
                lblQualidadeVinho.setText("Alta qualidade");
                lblQualidadeVinho.setForeground(Color.green);
            }

        } catch (Exception e) {
            System.out.println("Ocorreu um erro ao tentar abrir o arquivo.");
        }
    }
}
