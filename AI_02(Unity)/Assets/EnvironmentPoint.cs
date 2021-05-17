using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum EEnvironmentType
{
    GrassLand,
    Water,
    Mountain,
    Forest,

}

public class EnvironmentPoint : MonoBehaviour
{
    static private float angleEpsilon;

    struct BorderLineInfo
    {
        public EnvironmentPoint point;
        public Vector2 direction;
    }

    struct EnvironmentBorderInfo
    {
        public int frontIndex;
        public int rearIndex;
        Vector2 bisectorDirection;
    }

    private Vector2 position;
    private List<BorderLineInfo> connectLines;

    private Dictionary<EEnvironmentType, EnvironmentBorderInfo> environmentBorders;

    //public void AddEnvironmentBorder(EnvironmentPoint frontPoint, EnvironmentPoint rearPoint, EEnvironmentType inType, EEnvironmentType outType)
    //{

        
    //}

    private BorderLineInfo AddBorderLinePoint(Vector2 newPos)
    {
        Vector2 direction = (newPos - position);

        foreach (var lineInfo in connectLines)
        {
            if (Vector2.Angle(direction, lineInfo.direction) <= angleEpsilon)
            {

            }
        }

        BorderLineInfo result = new BorderLineInfo();

        return result;
    }

    private void CutAndDivideLine(EnvironmentPoint newPoint, EnvironmentPoint oldPoint)
    {

    }
}
