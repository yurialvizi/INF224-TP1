package RemoteControl;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToolBar;

public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;
    private JMenuBar menuBar;
    private JMenu menu;
    private JTextArea textArea;
    private JButton searchMediaButton;
    private JButton searchGroupButton;
    private JButton playMediaButton;
    private JButton exitButton;
    private JMenuItem searchMediaMenuItem;
    private JMenuItem searchGroupMenuItem;
    private JMenuItem playMediaMenuItem;
    private JMenuItem exitMenuItem;
    private JTextField textField;
    private JToolBar toolbar;
    private JScrollPane scrollPane;
    private ButtonAction searchMediaAction;
    private ButtonAction searchGroupAction;
    private ButtonAction playMediaAction;
    private ButtonAction exitAction;
    private ClientSocket clientSocket;

    public static void main(String[] args) throws Exception {
        new MainWindow();
    }

    public MainWindow() {
        // Set window properties
        setTitle("Example");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        textArea = new JTextArea();
        textArea.setSize(400, 300);
        scrollPane = new JScrollPane(textArea);
        scrollPane.setPreferredSize(new Dimension(200, 100));

        // add actions
        searchMediaAction = new ButtonAction(ButtonAction.Type.SEARCH_MEDIA, textArea, r -> sendRequest(r));
        searchGroupAction = new ButtonAction(ButtonAction.Type.SEARCH_GROUP, textArea, r -> sendRequest(r));
        playMediaAction = new ButtonAction(ButtonAction.Type.PLAY_MEDIA, textArea, r -> sendRequest(r));
        exitAction = new ButtonAction(ButtonAction.Type.EXIT, textArea, r -> sendRequest(r));

        // add menu
        menuBar = new JMenuBar();
        menu = new JMenu("File");
        searchMediaMenuItem = new JMenuItem(searchMediaAction);
        searchGroupMenuItem = new JMenuItem(searchGroupAction);
        playMediaMenuItem = new JMenuItem(playMediaAction);
        exitMenuItem = new JMenuItem(exitAction);
        menu.add(searchMediaMenuItem);
        menu.add(searchGroupMenuItem);
        menu.add(playMediaMenuItem);
        menu.add(exitMenuItem);
        menuBar.add(menu);
        setJMenuBar(menuBar);

        // Add toobar components
        textField = new JTextField(20);
        searchMediaButton = new JButton(searchMediaAction);
        searchGroupButton = new JButton(searchGroupAction);
        playMediaButton = new JButton(playMediaAction);
        exitButton = new JButton(exitAction);

        // add toolbar
        toolbar = new JToolBar();
        toolbar.setLayout(new FlowLayout());
        toolbar.add(textField);
        toolbar.add(searchMediaButton);
        toolbar.add(searchGroupButton);
        toolbar.add(playMediaButton);
        toolbar.add(exitButton);
        add(toolbar, BorderLayout.NORTH);

        add(scrollPane, BorderLayout.CENTER);

        pack();
        setVisible(true);

        clientSocket = new ClientSocket("localhost", 3331, this);
        clientSocket.conect();
    }

    public void sendRequest(String message) {
        if (clientSocket == null) {
            System.out.println("clientSocket is null");
            return;
        }
        String textFString = textField.getText();
        if (textFString == null || textFString.equals("")) {
            textArea.append("Empty media name\n");
            return;
        }
        clientSocket.sendRequest(message + " \"" + textField.getText() + "\"");
        textField.setText("");
    }

    public void setTextArea(String text) {
        textArea.append(text + "\n");
    }
}
