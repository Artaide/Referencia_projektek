package main;

import java.io.*;
import game.Player;
import game.utils.VehicleException;
import game.vehicles.*;


public class Main
{
    public static Player loadPlayerFromFile(String playerName)
    {
        File input = new File("users/" + playerName + ".txt");

        String[] data = null;
        try (BufferedReader bf = new BufferedReader(new FileReader(input))){
            String line = bf.readLine();
            data = line.split(" ");

            return new Player(playerName, data[0], Integer.parseInt(data[1]));
        } catch (IOException e) {
            System.out.println("IO error occured: " + e.getMessage());
        } catch (NumberFormatException ex) {
            return new Player(playerName, data[0], 0);
        }
        return null;
    }
    public static void main(String[] args)
    {
        Player Daniel = loadPlayerFromFile("Daniel");
        Player Peter = loadPlayerFromFile("Peter");
        Player Richard = loadPlayerFromFile("Richard");
        Player Tamas = loadPlayerFromFile("Tamas");
        Player Zorror = loadPlayerFromFile("Zorror");

        Car c1 = new Car(100, 5000);
        Car c2 = new Car(100, 6000);
        Car c3 = new Car(90, 4000);
        Car c4 = new Car(80, 3000);
        Car c5 = new Car(70, 2000);

        System.out.println("lefutottam");
    }
}
