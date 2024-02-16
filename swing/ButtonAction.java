import java.awt.event.ActionEvent;
import java.util.function.Consumer;

import javax.swing.AbstractAction;
import javax.swing.JTextArea;

public class ButtonAction extends AbstractAction {
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

    public ButtonAction(Type type, JTextArea textArea, Consumer<String> sendRequest) {
        super(type.getText());
        this.type = type;
        this.textArea = textArea;
        this.sendRequest = sendRequest;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
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
