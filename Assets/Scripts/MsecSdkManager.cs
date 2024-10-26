using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class MsecSdkManager : MonoBehaviour
{
    public Text RootedText;
    public Text MemoryHookedText;
    public Text EmulatorText;
    public Text WebviewdebuggableText;
    public Text DebuggableText;
    public Text ADBenabledText;
    private static MsecSdkManager _instance;
    //void Awake()
    //{
    //    if (_instance != null && _instance != this)
    //    {
    //        Destroy(this.gameObject);
    //    }
    //    else
    //    {
    //        _instance = this;
    //        DontDestroyOnLoad(this.gameObject);
    //    }
    //}

    //public static MsecSdkManager Instance
    //{
    //    get
    //    {
    //        if (_instance == null)
    //        {
    //            GameObject obj = new GameObject("MsecSdkManager");
    //            _instance = obj.AddComponent<MsecSdkManager>();
    //            DontDestroyOnLoad(obj);
    //        }
    //        return _instance;
    //    }
    //}

    void Start()
    {
        if (Application.platform == RuntimePlatform.Android)
        {
            InitMsecSdk();
        }
        else if(Application.platform == RuntimePlatform.IPhonePlayer)
        {
            InitMsecSdk();
        }
    }
#if UNITY_ANDROID
    private AndroidJavaObject msecSdk;

    public void InitMsecSdk()
    {
        string broker = "tcp://broker.msecsys.com:5566;tcp://broker.msecsys.com:5568;tcp://broker01.msecsys.com:5566;tcp://broker01.msecsys.com:5568;";
        string publisher = "tcp://pub.msecsys.com:5565";
        string appVersion = Application.version;

        try
        {
            using (AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer"))
            {
                AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
                msecSdk = new AndroidJavaObject("com.msecsys.msecsdk.MSecSdk"); 

                string packageName = activity.Call<string>("getPackageName");

                msecSdk.Call("init", broker, publisher, activity, packageName, appVersion, "unity", "msecsdk", "1.0.1");
                Debug.Log("MsecSdk initialized successfully.");

                UpdateUI();
            }
        }
        catch (System.Exception e)
        {
            Debug.LogError("Error initializing MsecSdk: " + e.Message);
        }
    }

    public bool IsRooted()
    {
        return msecSdk.Call<bool>("isRooted");
    }

    public bool IsHooked()
    {
        return msecSdk.Call<bool>("isHooked");
    }

    public bool IsEmulator()
    {
        return msecSdk.Call<bool>("isEmulator");
    }

    public bool IsWebviewDebuggable()
    {
        return msecSdk.Call<bool>("isWebviewDebuggable");
    }

    public bool IsDebuggable()
    {
        return msecSdk.Call<bool>("isDebuggable");
    }

    public bool IsADBEnabled()
    {
        return msecSdk.Call<bool>("isADBEnabled");
    }

    private void UpdateUI()
    {
        Debug.Log("Check Status MsecSdk: " + IsRooted() + " / " + IsHooked() + " / " + IsEmulator() + " / " + IsWebviewDebuggable() + " / " + IsDebuggable() + " / " + IsADBEnabled());
        if (RootedText != null) RootedText.text = "Rooted or Jailbroken : " + IsRooted();
        if (MemoryHookedText != null) MemoryHookedText.text = "Memory hooked : " + IsHooked();
        if (EmulatorText != null) EmulatorText.text = "Is an emulator : " + IsEmulator();
        if (WebviewdebuggableText != null) WebviewdebuggableText.text = "Webview debug: " + IsWebviewDebuggable();
        if (DebuggableText != null) DebuggableText.text = "Debuggable : " + IsDebuggable();
        if (ADBenabledText != null) ADBenabledText.text = "ADB enabled : " + IsADBEnabled();
    }
#elif UNITY_IOS
    [DllImport("__Internal")]
    private static extern void initMSecSdk(string appVersion);

    [DllImport("__Internal")]
    private static extern bool isJailbroken();

    [DllImport("__Internal")]
    private static extern bool isDebuggable();

    [DllImport("__Internal")]
    private static extern bool isMemoryHooked();

    [DllImport("__Internal")]
    private static extern bool isReverseEngineering();

    [DllImport("__Internal")]
    private static extern bool isEmulator();



    public void InitMsecSdk()
    {
        string appVersion = Application.version;
        initMSecSdk(appVersion);
        UpdateUI();
    }

    public bool IsRooted()
    {
        return isJailbroken();
    }

    public bool IsDebuggable()
    {
        return isDebuggable();
    }

    public bool IsHooked()
    {
        return isMemoryHooked();
    }

    public bool IsReverseEngineering()
    {
        return isReverseEngineering();
    }

    public bool IsEmulator()
    {
        return isEmulator();
    }
    private void UpdateUI()
    {
        Debug.Log("Check Status MsecSdk: " + IsRooted() + " / " + IsHooked() + " / " + IsEmulator() + " / " + IsReverseEngineering() + " / " + IsDebuggable() + " / ");
        RootedText.text = "Rooted or Jailbroken : " + IsRooted();
        MemoryHookedText.text = "Memory hooked : " + IsHooked();
        EmulatorText.text = "Is an emulator : " + IsEmulator();
        WebviewdebuggableText.text = "IsReverseEngineering: " + IsReverseEngineering();
        DebuggableText.text = "Debuggable : " + IsDebuggable();
    }

#endif

}