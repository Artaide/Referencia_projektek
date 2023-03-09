import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import auto.Auto;
import auto.utils.Color;

class Main
{
    public static Color getColor(String str)
    {
        Color value = Color.RED;
        switch (str)
        {
            case "GREEN":
                value = Color.GREEN;
                break;
            case "BLUE":
                value = Color.BLUE;
                break;
        }
        return value;
    }

    public static void main(String[] args)
    {
        Auto[] cars = new Auto[100];
        File input = new File("input.txt");
    
        try
        {
            int n = 0;
            String line = "";
            BufferedReader br = new BufferedReader(new FileReader(input));

            while ((line = br.readLine()) != null)
            {
                String[] parts = line.split(",");

                cars[n] = new Auto(parts[0], getColor(parts[1]), Integer.parseInt(parts[2]));
                n++;
            }
            br.close();
            for (int i = 0; i < n; i++)
            {
                System.out.println(cars[i].toString());
            }

        }
        catch (FileNotFoundException fe)
        {
            System.out.println("[ERROR] " + fe);
        }
        catch (IOException ioe)
        {
            System.out.println("[ERROR] " + ioe);
        }
    }
}