using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using WindowsFormsApp1;
using System.Runtime.InteropServices;
using System.IO;
using System.Drawing.Imaging;


namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;        // x position of upper-left corner
            public int Top;         // y position of upper-left corner
            public int Right;       // x position of lower-right corner
            public int Bottom;      // y position of lower-right corner
        }

        [DllImport("user32.dll")]
        private static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int x, int y, int width, int height, uint uFlags);

        [DllImport("user32.dll")]
        static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

        [DllImport("user32")]
        public static extern bool GetClientRect(IntPtr hwnd, out RECT lpRect);

        [DllImport("user32")]
        public static extern bool ScreenToClient(IntPtr hWnd, ref Point lpPoint);


        [DllImport("user32.dll")]
        static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, int dwExtraInfo);

        [DllImport("user32.dll")]
        private static extern IntPtr GetForegroundWindow();

        [DllImport("user32.dll")]
        public static extern bool SetForegroundWindow(IntPtr windowHandle);

        [DllImport("user32.dll")]
        public static extern bool RegisterHotKey(IntPtr hWnd, int id, KeyModifiers fsModifiers, Keys vk);

        [DllImport("user32.dll")]
        public static extern bool UnregisterHotKey(IntPtr hWnd, int id);

        public enum KeyModifiers
        {
            None = 0,
            Alt = 1,
            Control = 2,
            Shift = 4,
            Windows = 8
        }

        const int WM_HOTKEY = 0x0312;

        const uint MOUSEMOVE = 0x0001;      // 마우스 이동
        const uint ABSOLUTEMOVE = 0x8000;   // 전역 위치
        const uint LBUTTONDOWN = 0x0002;    // 왼쪽 마우스 버튼 눌림
        const uint LBUTTONUP = 0x0004;      // 왼쪽 마우스 버튼 떼어짐
        const uint RBUTTONDOWN = 0x0008;    // 오른쪽 마우스 버튼 눌림
        const uint RBUTTONUP = 0x00010;      // 오른쪽 마우스 버튼 떼어짐

        const int startMacroHotkeyId = 18181818;
        const int stopMacroHotkeyId = 18181819;
        const Keys startHotkey = Keys.F1;
        const Keys stopHotkey = Keys.F2;

        const string startKeword = "oexanima";
        const string endKeyword = "exanima01";
        const int itemSeedDataOffset = 31;
        const int itemSeedDataSize = 6;
        byte[] itemSeedBuffer = new byte[6];

        readonly Point TASKBAR_EXANIMA = new Point(905, 1060);

        readonly Point MAIN_BEGIN = new Point(958, 429);
        readonly Point CHARACTER_UNKNOWN = new Point(692, 403);
        readonly Point SHAPE_SKILL_NEXT = new Point(1650, 1000);
        readonly Point ABILITY_CALM = new Point(1204, 818);
        readonly Point ABILITY_BEGIN = new Point(1658, 1005);

        readonly Point MAIN_CONINUE = new Point(970, 485);
        readonly Point CHARACTER_CONINUE = new Point(1620, 1000);
        readonly Point MENU_ESCAPE = new Point(958, 619);

        readonly Point CHARACTER_DELETE = new Point(410, 117);
        readonly Point DELETE_OK = new Point(910, 570);

        readonly Point CAPTURE_INGAME_HP = new Point(850 - 1, 1016 - 1);
        readonly Point CAPTURE_INGAME_MENU_SETTING_E = new Point(883 - 1, 554 - 1);
        readonly Point CAPTURE_MAIN_EXIT_E = new Point(917 - 1, 729 - 1);
        readonly Point CAPTURE_CONTINUE_BACK = new Point(308 - 1, 1002 - 1);
        readonly Point CAPTURE_CONTINUE_BLACK = new Point(1329 - 1, 444 - 1);
        readonly Point CAPTURE_CONTINUE_DELETE_WINDOW = new Point(793 - 1, 525 - 1);
        readonly Point CAPTURE_BEGIN_HAIR_SKILL_COLOR = new Point(1636 - 1, 126 - 1);
        readonly Point CAPTURE_BEGIN_ABILITY_CALM = new Point(1212 - 1, 822 - 1);
        readonly Point CAPTURE_BEGIN_ABILITY_SENSEMINDS = new Point(959 - 1, 894 - 1);

        struct CapturedImageInfo
        {
            public readonly Point upperLeftPos;
            public readonly Bitmap capturedImage;

            public CapturedImageInfo(Point pos, Bitmap bitmap)
            {
                upperLeftPos = pos;
                capturedImage = bitmap;
            }
        }

        CapturedImageInfo main_exit_e, continue_delete_window, continue_back, hp_black, ingame_hp, ingame_menu_setting_e;
        CapturedImageInfo begin_shape_color, begin_skills_experience, begin_ability_senseminds;

        readonly Size defualtCompareImageSize = new Size(3, 3);
        Bitmap capturedImage;

        WindowsFormsApp1.Form1 dataAnalyzer = new WindowsFormsApp1.Form1();

        IntPtr exanimaHandle = IntPtr.Zero;
        string backupFileName;
        bool canLoopMacro = true;

        struct TeleportDataInfo
        {
            public string teleportDataFilePath;
            public byte[] teleportData;
            public int teleportDataSize;
        }

        TeleportDataInfo floor1End, floor2End, floor3End, catacombToEntry, floor1Arsenal;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Initialize();
        }

        public void Initialize()
        {
            dataAnalyzer.Initialize();

            if (CreateTeleportDataInfo(out floor1End, "Floor1End.rsg") == false)
            {
                MessageBox.Show("Floor1End에 대한 순간이동데이터 초기화 실패.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (CreateTeleportDataInfo(out floor2End, "Floor2End.rsg") == false)
            {
                MessageBox.Show("Floor2End에 대한 순간이동데이터 초기화 실패.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (CreateTeleportDataInfo(out floor3End, "Floor3End.rsg") == false)
            {
                MessageBox.Show("Floor3End에 대한 순간이동데이터 초기화 실패.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (CreateTeleportDataInfo(out catacombToEntry, "CatacombToEntry.rsg") == false)
            {
                MessageBox.Show("catacobmToEntry에 대한 순간이동데이터 초기화 실패.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (CreateTeleportDataInfo(out floor1Arsenal, "Floor1Arsenal.rsg") == false)
            {
                MessageBox.Show("floor1Arsenal 대한 순간이동데이터 초기화 실패.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            capturedImage = new Bitmap(defualtCompareImageSize.Width, defualtCompareImageSize.Height);

            main_exit_e = new CapturedImageInfo(CAPTURE_MAIN_EXIT_E, Resource_main_exit_e.capture_main_exit_e);
            continue_back = new CapturedImageInfo(CAPTURE_CONTINUE_BACK, Resource_continue_back.capture_continue_back);
            continue_delete_window = new CapturedImageInfo(CAPTURE_CONTINUE_DELETE_WINDOW, Resource_continue_delete_window.capture_continue_delete_window);
            begin_shape_color = new CapturedImageInfo(CAPTURE_BEGIN_HAIR_SKILL_COLOR, Resource_begin_shape_color.capture_begin_shape_color);
            begin_skills_experience = new CapturedImageInfo(CAPTURE_BEGIN_HAIR_SKILL_COLOR, Resource_begin_skills_experience.capture_begin_skills_experience);
            begin_ability_senseminds = new CapturedImageInfo(CAPTURE_BEGIN_ABILITY_SENSEMINDS, Resource_begin_ability_senseminds.capture_begin_ability_senseminds);
            hp_black = new CapturedImageInfo(CAPTURE_INGAME_HP, Resource_black.capture_begin_class_black);
            ingame_hp = new CapturedImageInfo(CAPTURE_INGAME_HP, Resource_ingame_hp.capture_ingame_hp);
            ingame_menu_setting_e = new CapturedImageInfo(CAPTURE_INGAME_MENU_SETTING_E, Resource_ingame_menu_setting_e.capture_ingame_menu_setting_e);

            RegisterHotKey(Handle, startMacroHotkeyId, KeyModifiers.None, startHotkey);
            RegisterHotKey(Handle, stopMacroHotkeyId, KeyModifiers.None, stopHotkey);
        }

        protected override void WndProc(ref Message message)
        {
            switch (message.Msg)
            {
                case WM_HOTKEY:
                    Keys key = (Keys)(((int)message.LParam >> 16) & 0xFFFF);
                    KeyModifiers modifier = (KeyModifiers)((int)message.LParam & 0xFFFF);

                    if (KeyModifiers.None == modifier && key == startHotkey)
                    {
                        HotKey_Event_Start();
                    }
                    else if (KeyModifiers.None == modifier && key == stopHotkey)
                    {
                        HotKey_Event_Stop();
                    }

                    break;
            }
            base.WndProc(ref message);
        }

        private void HotKey_Event_Start()
        {
            if (true == canLoopMacro)
            {
                ProcessLoopAutoNavigateGame();
            }

            //Teleport(DataBase.SingletonInstance.OpenPath, catacombToEntry);
        }

        private void HotKey_Event_Stop()
        {
            canLoopMacro = false;
            //button1.Enabled = true;
            //SetForegroundWindow(Handle);

            //Teleport(DataBase.SingletonInstance.OpenPath, floor2End);
        }

        private void ProcessLoopAutoNavigateGame()
        {
            Invoke(new Action(delegate
            {
                button1.Enabled = false;
            }));

            DataBase.SingletonInstance.OpenPath = @"C:\Users\kwans\AppData\Roaming\Exanima\Exanima001.rsg";
            dataAnalyzer.EnableOutputText = false;
            bool isProcessRunning = false;

            while (canLoopMacro)
            {
                if (isProcessRunning == false)
                {
                    var processes = Process.GetProcessesByName("Exanima");

                    if (0 == processes.Length)
                    {
                        ProcessMouseClick(TASKBAR_EXANIMA, 500);
                        Thread.Sleep(2000);
                        exanimaHandle = GetForegroundWindow();
                    }
                    else
                    {
                        exanimaHandle = processes[0].MainWindowHandle;
                    }
                }

                SetForegroundWindow(exanimaHandle);

                isProcessRunning = AutoNavigateGame();
            }

            Invoke(new Action(() =>
            {
                button1.Enabled = true;
            }));

            canLoopMacro = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ProcessLoopAutoNavigateGame();
        }

        private void FocusToExanima()
        {
            if (exanimaHandle != GetForegroundWindow())
            {
                //ProcessMouseClick(TASKBAR_EXANIMA, 500);
                SetForegroundWindow(exanimaHandle);
            }
        }

        private bool AutoNavigateGame()
        {
            if (canLoopMacro == false) return false;

            if (File.Exists(DataBase.SingletonInstance.OpenPath) == false && CreateCharacter() == false)
            {
                return false;
            }

            while (IsFileUsable(DataBase.SingletonInstance.OpenPath) == false)
            {
                Thread.Sleep(1000);
            }

            FileInfo fileInfo = new FileInfo(DataBase.SingletonInstance.OpenPath);
            if (null == fileInfo)
            {
                return false;
            }

            if (fileInfo.Length < 100)
            {
                File.Delete(DataBase.SingletonInstance.OpenPath);
                var processes = Process.GetProcessesByName("Exanima");

                if (0 != processes.Length)
                {
                    Thread.Sleep(2000);
                    processes[0].Kill();
                    Thread.Sleep(2000);
                }

                return false;
            }

            dataAnalyzer.BackupOriginalFile(true, false);

            if (canLoopMacro == false) return false;

            int dataSize = CalculateLocationDataSize(DataBase.SingletonInstance.OpenPath, true);

            if (dataSize == floor1End.teleportDataSize)
            {
                if (Teleport(DataBase.SingletonInstance.OpenPath, floor1End) == false)
                {
                    SetForegroundWindow(Handle);
                    MessageBox.Show("순간이동 실패", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }

                if (PlayNextFloor() == false) return false;

                dataSize = CalculateLocationDataSize(DataBase.SingletonInstance.OpenPath);
            }

            if (canLoopMacro == false) return false;

            if (dataSize == floor2End.teleportDataSize)
            {
                if (Teleport(DataBase.SingletonInstance.OpenPath, floor2End) == false)
                {
                    SetForegroundWindow(Handle);
                    MessageBox.Show("순간이동 실패", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }

                if (PlayNextFloor() == false) return false;
                dataSize = CalculateLocationDataSize(DataBase.SingletonInstance.OpenPath);
            }

            if (canLoopMacro == false) return false;

            if (dataSize == floor3End.teleportDataSize)
            {
                if (Teleport(DataBase.SingletonInstance.OpenPath, floor3End) == false)
                {
                    SetForegroundWindow(Handle);
                    MessageBox.Show("순간이동 실패", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }

                if (PlayNextFloor() == false) return false;
            }
            else
            {
                SetForegroundWindow(Handle);
                MessageBox.Show("현재 파일의 층수에 알맞은 순간이동 정보가 없음.", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            var myScore = new WindowsFormsApp1.Form1.MyScore();

            dataAnalyzer.ClearPanel();
            dataAnalyzer.DataAnalyze();
            backupFileName = dataAnalyzer.BackupCopyFileFromOriginalFile("no_item", myScore);

            Invoke(new Action(() =>
            {
                listBox1.Items.Add(backupFileName);

                if (listBox1.Items.Count > 100)
                {
                    listBox1.Items.Clear();
                }
            }));

            if (backupFileName.Contains('U') || myScore.Score >= 160)
            {
                backupFileName = dataAnalyzer.CreateBackupFilePath(backupFileName);
                File.Copy("lastModifiedBackup.rsg", backupFileName);
            }

            backupFileName = null;
            dataAnalyzer.ClearPanel();

            if (canLoopMacro == false) return false;

            if (DeleteCharacter() == false) return false;

            return true;
        }

        private bool DeleteCharacter()
        {
            FocusToExanima();
            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            ActionInfo<Point, int> clickMouse;
            clickMouse.action = ProcessMouseClick;
            clickMouse.parameter1 = MAIN_CONINUE;
            clickMouse.parameter2 = 300;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, main_exit_e, 1000, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(continue_back, 200, 20) == false)
            {
                return false;
            }

            clickMouse.parameter1 = CHARACTER_DELETE;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, continue_delete_window, 1000, 4) == false)
            {
                return false;
            }

            clickMouse.parameter1 = DELETE_OK;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, continue_delete_window, 500, 4, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            return true;
        }

        private bool CreateCharacter()
        {
            FocusToExanima();
            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            ActionInfo<Point, int> clickMouse;
            clickMouse.action = ProcessMouseClick;
            clickMouse.parameter1 = MAIN_BEGIN;
            clickMouse.parameter2 = 400;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, main_exit_e, 1000, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(hp_black, 300, 40) == false)
            {
                return false;
            }

            clickMouse.parameter1 = CHARACTER_UNKNOWN;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, begin_shape_color, 300, 10) == false)
            {
                return false;
            }

            clickMouse.parameter1 = SHAPE_SKILL_NEXT;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, begin_shape_color, 500, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(begin_skills_experience, 200, 10) == false)
            {
                return false;
            }

            clickMouse.parameter1 = SHAPE_SKILL_NEXT;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, begin_skills_experience, 500, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(begin_ability_senseminds, 200, 20) == false)
            {
                return false;
            }
            ProcessMouseClick(ABILITY_CALM);
            ProcessMouseClick(ABILITY_CALM, 300);

            clickMouse.parameter1 = ABILITY_BEGIN;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, begin_ability_senseminds, 500, 4, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(ingame_hp, 400, 50) == false)
            {
                return false;
            }

            ActionInfo<string> keyPress;
            keyPress.action = SendKeys.SendWait;
            keyPress.parameter = "{ESC}";
            if (RepeatActionUntilSameImageOnScreen(keyPress, ingame_menu_setting_e, 400, 10) == false)
            {
                return false;
            }

            clickMouse.parameter1 = MENU_ESCAPE;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, ingame_menu_setting_e, 2000, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            return true;
        }

        private bool PlayNextFloor()
        {
            FocusToExanima();
            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            ActionInfo<Point, int> clickMouse;
            clickMouse.action = ProcessMouseClick;
            clickMouse.parameter1 = MAIN_CONINUE;
            clickMouse.parameter2 = 300;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, main_exit_e, 1000, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(continue_back, 200, 20) == false)
            {
                return false;
            }

            clickMouse.parameter1 = CHARACTER_CONINUE;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, hp_black, 200, 20) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(ingame_hp, 400, 50) == false)
            {
                return false;
            }

            ActionInfo<string> keyPress;
            keyPress.action = SendKeys.SendWait;
            keyPress.parameter = "W";
            if (RepeatActionUntilSameImageOnScreen(keyPress, hp_black, 200, 30) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(hp_black, 400, 50, false) == false)
            {
                return false;
            }

            keyPress.parameter = "{ESC}";
            if (RepeatActionUntilSameImageOnScreen(keyPress, ingame_menu_setting_e, 400, 10) == false)
            {
                return false;
            }

            clickMouse.parameter1 = MENU_ESCAPE;
            if (RepeatActionUntilSameImageOnScreen(clickMouse, ingame_menu_setting_e, 2000, 2, false) == false)
            {
                return false;
            }

            if (WaitUntilSameImageOnScreen(main_exit_e, 300, 40) == false)
            {
                return false;
            }

            return true;
        }

        private void ProcessMouseClick(int x, int y, int waitTime = 0)
        {
            ProcessMouseClick(new Point(x, y), waitTime);
        }

        private bool IsFileUsable(string filePath)
        {
            try
            {
                using (File.Open(filePath, FileMode.Open)) { }
            }
            catch (IOException)
            {
                return false;
            }

            return true;
        }

        private bool WaitUntilSameImageOnScreen(CapturedImageInfo compareImageInfo, int minWaitTime = 200, int maxWaitCount = 10, bool condition = true)
        {
            for (int i = 0; i < maxWaitCount; ++i)
            {
                ScreenCapture(compareImageInfo.upperLeftPos, defualtCompareImageSize);
                //capturedImage.Save("222.bmp");

                if (CompareImage(capturedImage, compareImageInfo.capturedImage, new Size(3, 3)) == condition)
                {
                    return true;
                }

                Thread.Sleep(minWaitTime);
            }

            return false;
        }

        private bool RepeatActionUntilSameImageOnScreen(ActionInfo actionInfo, CapturedImageInfo compareImageInfo, int actionInterval = 200, int maxActionCount = 10, bool condition = true)
        {
            for (int i = 0; i < maxActionCount; ++i)
            {
                ScreenCapture(compareImageInfo.upperLeftPos, defualtCompareImageSize);

                //capturedImage.Save("222.bmp");

                if (CompareImage(capturedImage, compareImageInfo.capturedImage, new Size(3, 3)) == condition)
                {
                    return true;
                }

                actionInfo.ProcessAction();
                ScreenCapture(compareImageInfo.upperLeftPos, defualtCompareImageSize);

                //capturedImage.Save("222.bmp");

                if (CompareImage(capturedImage, compareImageInfo.capturedImage, new Size(3, 3)) == condition)
                {
                    return true;
                }

                Thread.Sleep(actionInterval);
            }

            return false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Teleport(DataBase.SingletonInstance.OpenPath, catacombToEntry);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Teleport(DataBase.SingletonInstance.OpenPath, floor2End);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            dataAnalyzer.Show();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Teleport(DataBase.SingletonInstance.OpenPath, floor1Arsenal);
        }

        private void ProcessMouseClick(Point point, int waitTime = 200)
        {
            Cursor.Position = point;

            mouse_event(LBUTTONDOWN, 0, 0, 0, 0);
            mouse_event(LBUTTONUP, 0, 0, 0, 0);

            Thread.Sleep(waitTime);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            UnregisterHotKey(Handle, startMacroHotkeyId);
            UnregisterHotKey(Handle, stopMacroHotkeyId);
        }

        private int CalculateLocationDataSize(string openFilePath, bool shouldRecordItemSeed = false)
        {
            int startIndex, endIndex;

            for (int i = 0; i < 10; ++i)
            {
                if (IsFileUsable(openFilePath)) break;

                Thread.Sleep(300);
            }

            using (StreamReader streamReader = new StreamReader(openFilePath, Encoding.ASCII))
            {
                string fileText = streamReader.ReadToEnd();

                startIndex = fileText.IndexOf(startKeword);
                endIndex = fileText.IndexOf(endKeyword, startIndex + 3);

                if (startIndex == -1 || endIndex == -1)
                {
                    return -1;
                }

                if (shouldRecordItemSeed)
                {
                    streamReader.BaseStream.Position = startIndex + itemSeedDataOffset;
                    streamReader.BaseStream.Read(itemSeedBuffer, 0, itemSeedDataSize);
                }
            }

            return endIndex - startIndex;
        }

        private bool Teleport(string toTeleportFilePath, TeleportDataInfo teleportDataInfo)
        {
            if (File.Exists(toTeleportFilePath) == false)
            {
                return false;
            }

            using (FileStream fileStream = new FileStream(toTeleportFilePath, FileMode.Open))
            {
                StreamReader streamReader = new StreamReader(fileStream, Encoding.ASCII);
                string fileText = streamReader.ReadToEnd();

                int startIndex = fileText.IndexOf(startKeword);
                int endIndex = fileText.IndexOf(endKeyword, startIndex + 3);

                if (startIndex == -1 || endIndex == -1 || endIndex - startIndex != teleportDataInfo.teleportDataSize)
                {
                    return false;
                }

                fileStream.Position = startIndex;
                fileStream.Write(teleportDataInfo.teleportData, 0, teleportDataInfo.teleportDataSize);

                fileStream.Position = startIndex + itemSeedDataOffset;
                fileStream.Write(itemSeedBuffer, 0, itemSeedDataSize);
            }

            return true;
        }

        private bool CreateTeleportDataInfo(out TeleportDataInfo teleportDataInfo, string teleportDataFilePath)
        {
            teleportDataInfo = new TeleportDataInfo();

            if (File.Exists(teleportDataFilePath) == false)
            {
                return false;
            }


            using (StreamReader streamReader = new StreamReader(teleportDataFilePath, Encoding.ASCII))
            {
                string fileText = streamReader.ReadToEnd();

                int startIndex = fileText.IndexOf(startKeword);
                int endIndex = fileText.IndexOf(endKeyword, startIndex + 3);
                if (startIndex == -1 || endIndex == -1)
                {
                    return false;
                }

                teleportDataInfo.teleportDataFilePath = teleportDataFilePath;
                teleportDataInfo.teleportDataSize = endIndex - startIndex;

                teleportDataInfo.teleportData = new byte[teleportDataInfo.teleportDataSize];
                streamReader.BaseStream.Position = startIndex;
                streamReader.BaseStream.Read(teleportDataInfo.teleportData, 0, teleportDataInfo.teleportDataSize);
            }

            return true;
        }

        private void ScreenCapture(Point screenUpperLeft, Size regionSize)
        {
            using (Graphics graphics = Graphics.FromImage(capturedImage))
            {
                graphics.CopyFromScreen(screenUpperLeft, Point.Empty, regionSize);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Thread.Sleep(4000);

            //var pos = Ca;

            //ScreenCapture(pos, new Size(3, 3));

            //capturedImage.Save("aa.bmp");

            //ScreenCapture(pos, new Size(50, 50));

            //capturedImage.Save("111.bmp");

            //Close();


            //ProcessMouseClick(TASKBAR_EXANIMA, 500);
            //if (IntPtr.Zero == exanimaHandle)
            //{
            //    exanimaHandle = GetForegroundWindow();
            //}

            //RECT rect;

            //if (GetClientRect(exanimaHandle, out rect) == false)
            //{
            //    int a = 10;
            //}

            //textTop.Text = rect.Top.ToString();
            //textBottom.Text = rect.Bottom.ToString();
            //textLeft.Text = rect.Left.ToString();
            //textRight.Text = rect.Right.ToString();

            //SetForegroundWindow(Handle);

            //var pos = Cursor.Position;
            //int a = 0;
        }

        Func<byte, byte, bool> IsMarginOfError = (value1, value2) => { return (Math.Abs(value2 - value1) < 10); };

        private bool CompareImage(Bitmap image1, Bitmap image2, Size comparisonRegion)
        {
            Color color1, color2;

            for (int i = 0; i < comparisonRegion.Width; i++)
            {
                for (int j = 0; j < comparisonRegion.Height; j++)
                {
                    color1 = image1.GetPixel(i, j);
                    color2 = image2.GetPixel(i, j);

                    if (!IsMarginOfError(color1.R, color2.R) || !IsMarginOfError(color1.G, color2.G) || !IsMarginOfError(color1.B, color2.B))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        interface ActionInfo
        {
            void ProcessAction();
        }

        struct ActionInfo<T1, T2> : ActionInfo
        {
            public Action<T1, T2> action;
            public T1 parameter1;
            public T2 parameter2;

            public void ProcessAction()
            {
                action(parameter1, parameter2);
            }
        }

        struct ActionInfo<T> : ActionInfo
        {
            public Action<T> action;
            public T parameter;

            public void ProcessAction()
            {
                action(parameter);
            }
        }
    }
}
