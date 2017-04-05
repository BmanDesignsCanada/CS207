using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

namespace KSPSource
{
	[KSPAddon(KSPAddon.Startup.Flight, false)]
	public class KSPSource : MonoBehaviour
	{
		private float lastUpdate = 0.0f;
		private float lastFixedUpdate = 0.0f;
		private float logInterval = 5.0f;

		private string _tag = "KSPSource ";

		Socket sender;
		byte[] bytes = new byte[1024];  

		/*
         * Caution: as it says here: http://docs.unity3d.com/Documentation/ScriptReference/MonoBehaviour.Awake.html,
         * use the Awake() method instead of the constructor for initializing data because Unity uses
         * Serialization a lot.
         */
		public KSPSource()
		{
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: Constructor");
		}

		/*
         * Called after the scene is loaded.
         */
		void Awake()
		{
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: Awake: " + this.name);
			IPEndPoint remoteEP = new IPEndPoint(IPAddress.Parse("127.0.0.1"),5000);  

			// Create a TCP/IP  socket.  
			sender = new Socket(AddressFamily.InterNetwork,   
				SocketType.Stream, ProtocolType.Tcp );

			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: Connecting to server");
			sender.Connect(remoteEP);  
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: Connected");
		}

		/*
         * Called next.
         */
		void Start()
		{
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: Start");
		}

		/*
         * Called every frame
         */
		void Update()
		{
			if ((Time.time - lastUpdate) > logInterval)
			{
				lastUpdate = Time.time;
				Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
					+ "][" + Time.time.ToString("0.0000") + "]: Update");
			}
		}

		/*
         * Called at a fixed time interval determined by the physics time step.
         */
		void FixedUpdate()
		{
			Vessel ActiveVessel = FlightGlobals.ActiveVessel;
			sender.Send(Encoding.ASCII.GetBytes(ActiveVessel.altitude.ToString ()+"\n"));
			if ((Time.time - lastFixedUpdate) > logInterval)
			{
				lastFixedUpdate = Time.time;
				Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
					+ "][" + Time.time.ToString("0.0000") + "]: FixedUpdate");

				byte[] msg = Encoding.ASCII.GetBytes("STATUS\n");  

				// Send the data through the socket.  
				sender.Send(msg);  

				// Receive the response from the remote device.  
				int bytesRec = sender.Receive(bytes);  
				Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
					+ "][" + Time.time.ToString("0.0000") + "]: "+
					Encoding.ASCII.GetString(bytes,0,bytesRec)); 
			}
		}

		/*
         * Called when the game is leaving the scene (or exiting). Perform any clean up work here.
         */
		void OnDestroy()
		{
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
			+ "][" + Time.time.ToString("0.0000") + "]: OnDestroy");
			sender.Shutdown(SocketShutdown.Both);  
			sender.Close();  
		}
	}
}

