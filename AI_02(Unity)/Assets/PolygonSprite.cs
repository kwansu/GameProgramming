using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class PolygonSprite : MonoBehaviour
{
    private PolygonCollider2D polygonCollider;
    private List<TextMesh> textList;

    public string fileName;
    public GameObject textObject;

    void Start()
    {
        polygonCollider = GetComponent<PolygonCollider2D>();
    }

    private void Update()
    {
        if (Input.GetKeyUp(KeyCode.Return))
        {
            SetupMesh();
            //DebugPolygon();
        }
    }

    void SetupMesh()
    {
        Mesh mesh = new Mesh();

        int vertexCount = polygonCollider.points.Length;
        Vector3[] vertices = new Vector3[vertexCount];

        int i = 0, j = 0;
        foreach (var point in polygonCollider.points)
        {
            vertices[i] = point;
            vertices[i].z = 0.0f;
            ++i;
        }

        int triCount = (vertexCount - 2) * 3;
        int[] triangles = new int[triCount];

        for (j = 0, i = 2; i < vertexCount; ++i)
        {
            triangles[j++] = 0;
            triangles[j++] = i - 1;
            triangles[j++] = i;
        }

        mesh.vertices = vertices;
        mesh.triangles = triangles;

        GetComponent<MeshFilter>().mesh = mesh;

        string filePath = "Assets/Meshs/";

        AssetDatabase.CreateAsset(mesh, filePath + fileName + ".asset");
    }

    void DebugPolygon()
    {
        if (textObject == null)
        {
            Debug.LogError(1);
        }

        if (textList == null)
        {
            textList = new List<TextMesh>();
        }

        int pointCount = polygonCollider.points.Length;

        Debug.Log("path count : " + polygonCollider.pathCount);
        Debug.Log("shape count : " + polygonCollider.shapeCount);
        Debug.Log("point count : " + pointCount);

        for (int i = 0; i < pointCount; ++i)
        {
            if (textList.Count <= i)
            {
                GameObject temp = Instantiate<GameObject>(textObject);
                textList.Add(temp.GetComponent<TextMesh>());
            }

            textList[i].text = i.ToString();
            textList[i].transform.position = polygonCollider.points[i];
        }
    }
}
