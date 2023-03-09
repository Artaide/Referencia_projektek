package game.vehicles;

import game.utils.*;

class Train extends Vehicle
{
    @Override
    public void accelerate(int amount) throws VehicleException
    {
        if (amount < 0)
            this.accelerateCurrentSpeed(amount / 10);
        else
            this.accelerateCurrentSpeed(amount);
    }
}
