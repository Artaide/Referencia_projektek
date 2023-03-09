package tests;

import game.*;
import main.*;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import org.junit.Test;

public class Tests
{
    //bruh
    @Test (Expected = IllegalArgumentException)
    public void nullPlayerIllegalArg()
    {
        assertEqual(Expected, new Player(null, "id", 500));
    }
}
