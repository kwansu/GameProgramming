using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Manager_EnvironmentPoint : MonoBehaviour
{
    List<EnvironmentPoint> environmentPoints = new List<EnvironmentPoint>();

    void SetupEnvironmentPoints()
    {
        // 기존 저장된 정점을 모두 지우고, 필드에 있는 모든 정점들을 다시 연결한다.
        environmentPoints.Clear();
        environmentPoints.CopyTo(this.GetComponentsInChildren<EnvironmentPoint>());


    }
}
