using System;
using System.Collections.Generic;

public struct Status_Human
{
    public Health hp;
    public Speed speed;
    public Sight sight;

}

public struct Status_Item
{

}

public struct Health
{
    private float value;

    public static implicit operator Health(float value)
    {
        return new Health { value = value };
    }

    public static implicit operator float(Health health)
    {
        return health.value;
    }
}

public struct Sight
{
    private float value;

    public static implicit operator Sight(float value)
    {
        return new Sight { value = value };
    }

    public static implicit operator float(Sight sight)
    {
        return sight.value;
    }
}

public struct Speed
{
    private float value;

    public static implicit operator Speed(float value)
    {
        return new Speed { value = value };
    }

    public static implicit operator float(Speed speed)
    {
        return speed.value;
    }
}