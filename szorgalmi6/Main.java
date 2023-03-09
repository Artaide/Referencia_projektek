import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Main
{
    public static void main(String[] args)
    {
        File input = new File("in.txt");
        File output = new File("out.txt");

        try
        {
            BufferedReader br = new BufferedReader(new FileReader(input));
            PrintWriter pw = new PrintWriter(output);

            String[] results = new String[255];
            int[] fst = new int[255];
            int[] nums = new int[255];
            String[] nums_str = new String[255];
            int n = 0, m = 0;
            String line = "";
            String[] lines = new String[255];

            while ((line = br.readLine()) != null)
            {
                lines = line.split(" ");
                fst[n] = Integer.parseInt(lines[0]);
                nums_str[n] = lines[1];
                n++;
            }
            br.close();

            lines = nums_str[0].split(",");
            while (m < lines.length)
            {
                nums[m] = Integer.parseInt(lines[m]);
                m++;
            }

            for (int i = 0; i < n; i++)
            {
                StringBuilder sb1 = new StringBuilder();
                sb1.append(fst[i] + " none");
                results[i] = sb1.toString();
            }
            
            for (int k = 0; k < n; k++)
            {
                for (int i = 0; i < m; i++)
                {
                    for (int j = i; j < m-1; j++)
                    {
                        StringBuilder sb2 = new StringBuilder();
                        int sum = nums[i] + nums[j+1];
                        if (sum == fst[k])
                        {
                            sb2.append(fst[k] + " " + nums[i] + " " + nums[j+1]);
                            results[k] = sb2.toString();
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++)
                pw.print(results[i] + System.lineSeparator());
            pw.close();

        }
        catch (FileNotFoundException f)
        {
            System.out.println("Unable to open file: " + f.getMessage());
        }
        catch (IOException io)
        {
            System.out.println("IOException thrown: " + io.getMessage());
        }
    }
}