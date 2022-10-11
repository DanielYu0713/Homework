import java.awt.*;

import javax.security.auth.login.CredentialExpiredException;
import javax.swing.*;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Random;

import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;
import javax.swing.border.BevelBorder;

class vari{
	static int num = 0;
	static int h = 0;
	static int win=0;
	static int v=0;
}

public class HitMouses extends JFrame implements ActionListener, MouseListener{
	private static final long serialVersionUID = 1L;
	private Timer timer;
	private Random uRandom;
	private JLabel jLabelMouse, timesShowLabel, timesHitLabel, gradeLabel, heartLabel,jLabelpeo;
	private int timesShow = 0, timesHit = 0, grade = 1, delay = 1000,heart = 3;
	private Font font = new Font("", Font.BOLD, 20);
	private boolean isHit=false;
	private JMenu menuGame, menuHelp;
	private JMenuItem menuItemSatrt, menuItemEnd, menuItemHelp;

	public HitMouses() {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setBounds(200, 100, 700, 430);
		this.mySetBackground();
		this.mySetJLabelMouse();
		this.mySetCursorImage(1);
		this.addMouseListener(this);
		this.setTitle("HitMouse");
		timer = new Timer(1000, new myActionListener());
		uRandom = new Random();
		addJPanel();
		addMenu();
		timer.start();
		this.setVisible(true);
	}
	
	private void addMenu() {
		JMenuBar menuBar = new JMenuBar();
		menuGame = new JMenu("Game");
		menuHelp = new JMenu("Help");
		menuItemSatrt = new JMenuItem("Start");
		menuItemEnd = new JMenuItem("End");
		menuItemHelp = new JMenuItem("About");
		menuItemSatrt.addActionListener(this);
		menuItemEnd.addActionListener(this);
		menuItemHelp.addActionListener(this);
		menuGame.add(menuItemSatrt);
		menuGame.addSeparator();
		menuGame.add(menuItemEnd);
		menuHelp.add(menuItemHelp);
		menuBar.add(menuGame);
		menuBar.add(menuHelp);
		this.setJMenuBar(menuBar);
	}
	
	private void addJPanel() {

		
		JPanel panel = new JPanel();
		panel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		panel.setPreferredSize(new Dimension(700, 500));
		panel.setOpaque(false);
		
		/*timesShowLabel = new JLabel("0",
		new ImageIcon("1-1.png"), SwingConstants.CENTER);*/
		
		gradeLabel = new JLabel("1", new ImageIcon("1-2.png"),
		SwingConstants.CENTER);
		
		timesHitLabel = new JLabel("0",
		new ImageIcon("1-1.png"), SwingConstants.CENTER);

		heartLabel = new JLabel("3",
		new ImageIcon("1-3.png"), SwingConstants.CENTER);

		/*timesShowLabel.setFont(font);
		timesShowLabel.setSize(146, 40);*/
		gradeLabel.setFont(font);
		gradeLabel.setSize(146, 40);
		timesHitLabel.setFont(font);
		timesHitLabel.setSize(146, 40);
		heartLabel.setFont(font);
		heartLabel.setSize(146, 40);

		


		//panel.add(timesShowLabel);
		panel.add(timesHitLabel);
		panel.add(gradeLabel);
		panel.add(heartLabel);
		this.getContentPane().add(panel);
	}

	private void mySetCursorImage(int i) {
		Toolkit tool = Toolkit.getDefaultToolkit();
		Image image = tool.createImage("bar1_" + i + ".png");
		Cursor cursor = tool.createCustomCursor(image, new Point(10, 10), "lq");
		this.setCursor(cursor);
	}

	private void mySetJLabelMouse() {
		ImageIcon image=new ImageIcon();
		ImageIcon peoimg=new ImageIcon();
		vari.num = (int) (Math.random()*4)+1;
		peoimg= new ImageIcon("main.png");
		image = new ImageIcon("mouse"+vari.num+"-1.png");
		jLabelpeo = new JLabel(peoimg);
		jLabelMouse = new JLabel(image);
		jLabelpeo.setBounds(56, 63,100, 100);
		if(vari.win==1)
			jLabelMouse.setBounds(56, 63,300, 281);
		else
			jLabelMouse.setBounds(56, 63, 150, 150);
			this.getContentPane().add(jLabelpeo);
			this.getContentPane().add(jLabelMouse);
		
		if(vari.num==5)
			jLabelMouse.setVisible(true);
		else
			jLabelMouse.setVisible(false);
		
		jLabelpeo.setVisible(false);
		jLabelpeo.addMouseListener(this);
		jLabelMouse.addMouseListener(this);
	}

	private void mySetMouseImage(int i) {
		ImageIcon image = new ImageIcon();
		if(vari.num==5)
			image = new ImageIcon("mouse5-1.png");
		else
			image = new ImageIcon("mouse"+ vari.num + "-" + i + ".png");
		jLabelMouse.setIcon(image);
		jLabelMouse.setVisible(true);

		ImageIcon peoimg = new ImageIcon();
		peoimg = new ImageIcon("main.png");
		jLabelpeo.setIcon(peoimg);
		if(vari.v==1)
			jLabelpeo.setVisible(true);
	}

	private void mySetBackground() {
		((JPanel) this.getContentPane()).setOpaque(false);
		Icon image=new ImageIcon();
		image = new ImageIcon("back_sea.png");

		JLabel backLabel = new JLabel(image);
			backLabel.setBounds(0, 0, image.getIconWidth(), image.getIconHeight());
		this.getLayeredPane().add(backLabel, new Integer(Integer.MIN_VALUE));
	}

	public static void main(String[] args) {
		new HitMouses();
	}

	private class myActionListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			int ran = uRandom.nextInt(9);
			if(vari.win==1)
			{
				jLabelpeo.setVisible(false);
				vari.num = 5;

				jLabelMouse.setLocation(250, 100); 
				jLabelpeo.setLocation(350,120);
						
				vari.v=(int)(Math.random()*2);
				
			}	
			else
			{
				vari.num = (int) (Math.random()*4)+1;
				switch (ran) {
				case 0:
					jLabelMouse.setLocation(120, 55); 
					break;
				case 1:
					jLabelMouse.setLocation(285, 55);  
					break; 
				case 2:
					jLabelMouse.setLocation(440, 55); 
					break;
				case 3:
					jLabelMouse.setLocation(70, 130); 
					break;
				case 4:
					jLabelMouse.setLocation(260, 130);
					break;
				case 5:
					jLabelMouse.setLocation(410, 130);
					break;
				case 6:
					jLabelMouse.setLocation(130, 205);
					break;
				case 7:
					jLabelMouse.setLocation(285, 205);
					break;
				case 8:
					jLabelMouse.setLocation(440, 205);
					break;
				}	
			}
			mySetMouseImage(1);
			if(vari.win==1&&mouseShowTimes()<=0){
				end();
				int yes = JOptionPane.showConfirmDialog(HitMouses.this,
						"try again?", "lose", JOptionPane.YES_NO_OPTION);
				if (yes == JOptionPane.YES_NO_OPTION) {
					start();
				}
			}
			else if (mouseShowTimes()<=0) {
				end();
				int yes = JOptionPane.showConfirmDialog(HitMouses.this,
						"lose qq \n again?", "lose", JOptionPane.YES_NO_OPTION);
				if (yes == JOptionPane.YES_NO_OPTION) {
					start();
				}
			}
		}

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == menuItemSatrt) {
			start();
			return;}
		if (e.getSource() == menuItemEnd) {
			if (JOptionPane.showConfirmDialog(this, "out") == 0) {
				System.exit(0);
			}
			return;
		}
		if (e.getSource() == menuItemHelp) {
			JDialog dialog = new JDialog(this, "rule:");
		
			dialog.setBounds(this.getX()+20, this.getY()+20, 250, 160);
			dialog.setLayout(new GridLayout(5, 1));
			dialog.add(new JLabel("rule"));
			dialog.add(new JLabel("1) 25 points to next level"));
			dialog.add(new JLabel("2) 3 degree win"));
			dialog.add(new JLabel("3) hit bomb lose 1 heart"));
			dialog.add(new JLabel("4) miss 3 times lose 1 heart"));
			dialog.setVisible(true);
		}

	}

	public void end() {
		timer.stop();
	}

	public void start() {
		mySetMouseImage(1);
		timesShow = 0;
		timesHit = 0;
		grade = 1;
		heart=3;
		delay = 1000;
		if(vari.win==1)
			grade = 4;
		//timesShowLabel.setText("" + timesShow);
		timesHitLabel.setText("" + timesHit);
		gradeLabel.setText("" + grade);
		heartLabel.setText("" + heart);
		timer.start();
		setDelay(0);}

	public int mouseShowTimes() {
	//	timesShow++;
	//timesShowLabel.setText("" + timesShow);
		if(vari.num==4&&isHit == true)
			{	heart--;
				vari.h=0;
			}
		else if(vari.num==4&&isHit == false)
			vari.h=0;
			
		if(vari.num<4&&isHit==false)
			vari.h++;
		if(vari.num!=4&&vari.h==3)
			{
				heart--;
				vari.h=0;
			}
		if(jLabelpeo.isVisible()&&isHit==true)
			{
				heart--;
			}
		heartLabel.setText("" + heart);
		isHit = false;
		return heart;
	}

	public int mouseHitTimes() 
	{
		if(vari.num==1)
			timesHit++;
		else if(vari.num==2)
			timesHit+=2;
		else if(vari.num==3)
			timesHit+=3;
		else if(vari.num==5&&!jLabelpeo.isVisible())
			timesHit+=1;
		//heartLabel.setText("" + heart);
		timesHitLabel.setText("" + timesHit);
		return timesHit;
	}

	public int mouseGrade() {
		grade++;
		gradeLabel.setText("" + grade);
		return grade;
	}
	

	public void setDelay(int d) {
		if (timer != null) {
			delay += d;
			if (delay < 290) {
				delay = 1000;
			}
			timer.setDelay(delay);
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
	}


	@Override
	public void mousePressed(MouseEvent e)
	{
		mySetCursorImage(2);
		if (e.getSource() == jLabelMouse && !isHit)
		 {
			isHit = true;
			mySetMouseImage(2);
			if(vari.win==1&&mouseHitTimes()>=30)
				{
					end();
					vari.win=0;
					jLabelpeo.setVisible(false);
					int a = JOptionPane.showConfirmDialog(this, "want again?", "congraduation!!!", JOptionPane.YES_NO_OPTION);
					if (a == JOptionPane.YES_OPTION)
						{ 
							
							vari.v=0;
							start();
						} 
			}
			if (vari.num<5&&mouseHitTimes() >= 25)
			{
				setDelay(-180);
				if (mouseGrade() >= 4)
				{
					end();
					jLabelMouse.setVisible(false);
					int a = JOptionPane.showConfirmDialog(this, "want to challenge demon king?", "congraduation!!!", JOptionPane.YES_NO_OPTION);
					 if (a == JOptionPane.YES_OPTION)
					 { 
						 vari.win=1;
						start();
					 } 
				}
				timesShow = -1; timesHit = -1;mouseShowTimes();   mouseHitTimes();
			}
			vari.h = 0;
			mouseShowTimes();   
			
		} 
	}
	@Override public void mouseReleased(MouseEvent e)
	{
		mySetCursorImage(1);} @Override public void mouseEntered(MouseEvent e)
		{
	} @Override public void mouseExited(MouseEvent e) 
	{
						 
	} 
						
}
