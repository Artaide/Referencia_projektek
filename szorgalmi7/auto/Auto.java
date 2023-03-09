package auto;
import auto.utils.Color;

public class Auto
{ 
    String license;
    Color coloring;
    int maxvelocity, counter = 0;

    public Auto(String lic, Color col, int maxv)
    {
        license = lic;
        coloring = col;
        maxvelocity = maxv;
        counter++;
    }

    public Auto()
    {
        license = "AAA-000";
        coloring = Color.BLUE;
        maxvelocity = 120;
    }

    public boolean CompareSpeed(Auto car1, Auto car2)
    {
        return car1.maxvelocity > car2.maxvelocity;
    }

    //magamnak
    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        sb.append(license);
        switch (coloring)
        {
            case RED:
                sb.append(", RED, ");
                break;
            case GREEN:
                sb.append(", GREEN, ");
                break;
            case BLUE:
                sb.append(", BLUE, ");
                break;
            default:
                break;
        }
        sb.append(Integer.toString(maxvelocity));
        sb.append("\n");
        
        return sb.toString();
    }
}
