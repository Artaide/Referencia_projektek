package util;

public class IntVector
{
    int[] numbers;

    public IntVector(int[] numbers)
    {
        this.numbers = numbers;
    }

    public void add(int n)
    {
        for (int i = 0; i < numbers.length-1; i++)
            numbers[i] += n;
    }

    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        sb.append("[ ");
        for (int i = 0; i < numbers.length; i++)
            sb.append(numbers[i] + " ");
        sb.append("]");

        return sb.toString();
    }
}