import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * This class represents a client socket that connects to a server using a specified server URI and port.
 * It provides methods to establish a connection, send requests, and close the connection.
 */
public class ClientSocket {
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    private final String serverURI;
    private final int port;
    private final MainWindow gui;

    /**
     * Constructs a ClientSocket object with the specified server URI, port, and GUI.
     *
     * @param serverURI the server URI to connect to
     * @param port the port number to connect to
     * @param gui the MainWindow object associated with the client socket
     */
    public ClientSocket(String serverURI, int port, MainWindow gui) {
        this.serverURI = serverURI;
        this.port = port;
        this.gui = gui;
    }

    /**
     * Establishes a connection to the server.
     * Initializes the input and output streams for communication.
     */
    public void connect() {
        try {
            socket = new Socket(serverURI, port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * Sends a request to the server and receives the response.
     * Updates the GUI with the received response.
     *
     * @param request the request to send to the server
     */
    public void sendRequest(String request) {
        try {
            out.println(request);
            String line = in.readLine();
            while (!line.equals("|")) {
                gui.setTextArea(line);
                line = in.readLine();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Closes the connection to the server.
     * Closes the input and output streams and the socket.
     */
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
