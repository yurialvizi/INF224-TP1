import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientSocket {
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    private final String serverURI;
    private final int port;
    private final MainWindow gui;

    public ClientSocket(String serverURI, int port, MainWindow gui) {
        this.serverURI = serverURI;
        this.port = port;
        this.gui = gui;
    }

    public void conect() {
        try {
            socket = new Socket(serverURI, port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public void sendRequest(String request) {

        try {
            out.println(request);
            String line =  in.readLine();
            while(!line.equals("|")) {
                gui.setTextArea(line);
                line = in.readLine();

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void closeConnection() {
        try {
            in.close();
            out.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
