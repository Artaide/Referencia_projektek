package game;

import java.util.ArrayList;
import game.vehicles.*;

public class Player
{
    private String name, ip;
    private int credit;
    private ArrayList<Car> cars;

    public Player(String iname, String iip, int icredit)
    {
        if (iname == null || iip == null || iip.length() < 1 || vanWhiteSpace(iip) || icredit < 0)
            throw new IllegalArgumentException();
        else
        {
            name = iname;
            ip = iip;
            credit = icredit;
            cars = new ArrayList<>();
        }
    }

    //magamnak
    private boolean vanWhiteSpace(String str)
    {
        boolean van = false;
        for (char c : str.toCharArray())
        {
            if (Character.isWhitespace(c))
                van = true;
        }
        return van;
    }
}