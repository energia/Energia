package processing.app;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ToolChainManager {

    private boolean windowIsOpen = false;
    private static ToolchainManagerWindow window;

    public ToolChainManager() {
        //Может что-то сюда придется добавить, какие-нибудь поля
    }

    public boolean isOpen(){
        return windowIsOpen;
    }

    public void run() {
        //Первым делом открываем новое окно, где все что нужно спрашиваем у пользователя
        window = new ToolchainManagerWindow("Add new target");
        window.setVisible(true);
        windowIsOpen = true;
        System.out.println("Now we can add new targets(boards)");

        //Сделать наверное метод для закрытия...и тогда поставить windowIsOpen на false

        //Надо сделать так, чтобы нельзя было открыть новое окно, пока старое не закрыто!
        //В менеджере вся работа, открытие окна, и добавление папок с платами
        //А еще это надо вынести либо в отдельную функцию, либо в класс()

        //Возможно сюда надо будет добваить разные варианты того, что добавить
        //boardsWidget.add(new JMenuItem("Empty1"));
        //boardsWidget.add(new JMenuItem("Empty2"));

        //Названия плат хранятся в target.getBoards().get(board).get("name")
        //Надо сделать так, что мы будем итерироваться по всем существующим платам
        //(по созданным объектам платам, и выписывать их имена.)

//        JMenuItem item = new JRadioButtonMenuItem(action);
        /*
        group.add(item);
        menu.add(item);

        //Надо понять, что это за target такие
        /*
        if (target.getName().equals(Preferences.get("target")) &&
                board.equals(Preferences.get("board"))) {
            item.setSelected(true);
        }
        group.add(item);
        menu.add(item);
        */

        //                JFrame addWindow = new JFrame("Add new target");
//                addWindow.setVisible(true);

//                JMenu fileMenu = new JMenu("Файл");
//                fileMenu.add(new JMenuItem("Новый"));
        //addWindow.add(fileMenu);
//                addWindow.setSize(250, 250);
        //System.out.println("Open new window");
    }

    private class ToolchainManagerWindow extends JFrame implements ActionListener {

        final int EDGE = Base.isMacOS() ? 20 : 13;
        static final int SMALL = 6;
        static final int BUTTONGAP = 12; // 12 is correct for Mac, other numbers may be required for other platofrms

        JTextField boardNameField;
        JTextField smthElseField;

        String boardNameString;
        String smtElseString;

        JButton cancelButton;
        JButton addButton;

        public ToolchainManagerWindow(String title) throws HeadlessException {

            super(title);
            setResizable(false);
            //Добвить сюда всякие штуки

            Container pane = getContentPane();
            pane.setLayout(null);

            //Добавили лейблы к окнам ввода (нужно будет добавлять то, что надо ввести : имя платы, еще что-то)
            JLabel boardNameLabel = new JLabel("Enter new board name");
            JLabel smtElseLabel = new JLabel("Enter smth else");
            pane.add(boardNameLabel);
            pane.add(smtElseLabel);

            //Добавили поля для ввода (количество символов?)
            pane.add(boardNameField = new JTextField(30));
            pane.add(smthElseField = new JTextField(30));

            if (boardNameString != null) boardNameField.setText(boardNameString);
            if (smtElseString != null) smthElseField.setText(smtElseString);

            //Добавляем кнопочки
            JPanel buttons = new JPanel();
            buttons.setLayout(new FlowLayout(FlowLayout.CENTER, BUTTONGAP, 0));

            // ordering is different on mac versus pc
            if (Base.isMacOS()) {
                buttons.add(cancelButton = new JButton("Cancel"));
                buttons.add(addButton = new JButton("Add Board"));

            } else {
                buttons.add(addButton = new JButton("Add Board"));
                buttons.add(cancelButton = new JButton("Cancel"));
            }
            pane.add(buttons);

            // to fix ugliness.. normally macosx java 1.3 puts an
            // ugly white border around this object, so turn it off.
            if (Base.isMacOS()) {
                buttons.setBorder(null);
            }

            //Задаем размеры созданных элементов
            Dimension labelDimension = boardNameLabel.getPreferredSize();
            Dimension buttonsDimension = buttons.getPreferredSize();

            int buttonBlockWidth = buttonsDimension.width - 2 * BUTTONGAP;

            int fieldHeight = boardNameField.getPreferredSize().height;
            int fieldWidth = boardNameField.getPreferredSize().width;

            int labelWidth = boardNameLabel.getPreferredSize().width;

            // +1 since it's better to tend downwards
            int yoff = (1 + fieldHeight - labelDimension.height) / 2; //Господи, зачем это?

            int ypos = EDGE; //Верхний отступ

            //Это просто жесть какая-то, но тут мы прописываем, куда встанет первый лейбл и поле
            boardNameLabel.setBounds(EDGE + (labelDimension.width - labelWidth), ypos + yoff,
                    labelWidth, labelDimension.height);
            boardNameField.setBounds(EDGE + labelDimension.width + SMALL, ypos,
                    fieldWidth, fieldHeight);

            ypos += fieldHeight + SMALL; // Добавили высоту после добавления первой записи

            //Это просто жесть какая-то, но тут мы прописываем, куда встанет второй лейбл и поле
            labelWidth = smtElseLabel.getPreferredSize().width;
            smtElseLabel.setBounds(EDGE + (labelDimension.width - labelWidth), ypos + yoff,
                    labelWidth, labelDimension.height);
            smthElseField.setBounds(EDGE + labelDimension.width + SMALL, ypos,
                    fieldWidth, fieldHeight);

            //Еще отступы по высоте после второй записи
            ypos += fieldHeight + SMALL;
            ypos += fieldHeight + SMALL;

            //А тут ставится положение кнопок
            buttons.setBounds(labelWidth + fieldWidth - 100, ypos,
                    buttonsDimension.width, buttonsDimension.height);

            ypos += buttonsDimension.height + EDGE; //Еще высота (высота кнопок)

            int wide = labelWidth + fieldWidth + 6 * EDGE;
            int high = ypos + 2 * EDGE;

            //Вроде устанавливает оптимальный размер контейнера...для винды...??
            pack();

            setSize(wide, high);

            setLocationRelativeTo(null); // center

            cancelButton.addActionListener(this);
            addButton.addActionListener(this);
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            Object source = e.getSource();
            if (source == cancelButton) {
                closeWindow();
            } else if (source == addButton) {
                addTarget();
            }
        }
    }

    private void closeWindow() {
        window.setVisible(false);
        windowIsOpen = false;
    }

    private void addTarget(){

    }
}
