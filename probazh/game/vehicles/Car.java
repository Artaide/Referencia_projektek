package game.vehicles;

import game.utils.VehicleException;

public class Car extends Vehicle
{
    private final int maxSpeed;
    private final int price;
    public Car(int imaxSpeed, int iprice)
    {
        maxSpeed = imaxSpeed;
        price = iprice;
    }

    @Override
    public void accelerate(int amount) throws VehicleException
    {
        if (this.getCurrentSpeed() + amount < maxSpeed)
            accelerateCurrentSpeed(amount);
    }

    public String toString()
    {
        return "id: " + id + ", maxSpeed: " + maxSpeed + ", price" + price;
    }
}
