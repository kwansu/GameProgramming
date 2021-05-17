using System;

public static class ExtensionFloat
{
    public static bool Equels(this float value, float compare)
    {
        return Math.Abs(value - compare) <= float.Epsilon;
    }
}