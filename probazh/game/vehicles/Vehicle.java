package game.vehicles;

import game.utils.*;

abstract public class Vehicle
{
    protected final int id;
    private static int counter = 0;
    private double currentSpeed;

    public Vehicle()
    {
        id = counter++;
    }

    public double getCurrentSpeed()
    {
        return currentSpeed;
    }

    protected final void accelerateCurrentSpeed(int amount) throws VehicleException
    {
        double tmp = this.currentSpeed + amount;
        if (tmp < 0)
            throw new VehicleException("Invalid amount");
        else
            this.currentSpeed = tmp;
            
    }

    abstract public void accelerate(int amount) throws VehicleException;
}