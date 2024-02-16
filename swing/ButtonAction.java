import java.awt.event.ActionEvent;
import java.util.function.Consumer;

import javax.swing.AbstractAction;
import javax.swing.JTextArea;

/**
 * The ButtonAction class represents an action performed by a button in a Swing application.
 * It extends the AbstractAction class and implements the ActionListener interface.
 */
public class ButtonAction extends AbstractAction {
    /**
     * The Type enum represents the different types of button actions.
     */
    public enum Type {
        SEARCH_MEDIA("Search Media"),
        SEARCH_GROUP("Search Group"),
        PLAY_MEDIA("Play Media"),
        EXIT("Exit");

        private String text;

        Type(String text) {
            this.text = text;
        }

        public String getText() {
            return text;
        }
    }

    private JTextArea textArea;
    private Type type;
    private Consumer<String> sendRequest;

    /**
     * Constructs a ButtonAction object with the specified type, text area, and send request consumer.
     * 
     * @param type The type of the button action.
     * @param textArea The text area where the action result will be displayed.
     * @param sendRequest The consumer that sends the request associated with the button action.
     */
    public ButtonAction(Type type, JTextArea textArea, Consumer<String> sendRequest) {
        super(type.getText());
        this.type = type;
        this.textArea = textArea;
        this.sendRequest = sendRequest;
    }

    /**
     * Performs the action associated with the button.
     * 
     * @param e The action event.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        textArea.append("\n");
        switch (type) {
            case SEARCH_MEDIA:
                textArea.append("Searching media...\n");
                break;
            case SEARCH_GROUP:
                textArea.append("Searching group...\n");
                break;
            case PLAY_MEDIA:
                textArea.append("Playing media...\n");
                break;
            case EXIT:
                System.exit(0);
                break;
        }
        sendRequest.accept(type.getText().toLowerCase());
    }
}
