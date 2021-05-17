using System.Runtime.InteropServices;

namespace SingleGameMacro
{
    [StructLayout(LayoutKind.Explicit)]
    public partial struct ReturnInfo
    {
        [FieldOffset(0)]
        public int returnCode;

        // 리턴코드와 유니온된 상태
        [FieldOffset(0)]
        public bool isTrue;

        [FieldOffset(sizeof(int))]
        public string returnReason;

        public ReturnInfo(string returnReason = null, int returnCode = 0)
        {
            this.returnCode = returnCode;
            this.isTrue = (returnCode == 0);
            this.returnReason = returnReason;
        }

        public ReturnInfo(bool isTrue, string returnReason = null)
            : this(returnReason, (isTrue ? 1 : 0))
        {

        }
    }

    // public static object
    partial struct ReturnInfo
    {
        static public readonly ReturnInfo containKey = new ReturnInfo("이미 포함되어있습니다.");

        // bool 값에 대한 암시적 변환
        public static implicit operator ReturnInfo(bool input)
        {
            return new ReturnInfo(input);
        }
    }
}
