using System;
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
			if ((Time.time - lastFixedUpdate) > logInterval)
			{
				lastFixedUpdate = Time.time;
				Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
					+ "][" + Time.time.ToString("0.0000") + "]: FixedUpdate");
			}
		}

		/*
         * Called when the game is leaving the scene (or exiting). Perform any clean up work here.
         */
		void OnDestroy()
		{
			Debug.Log(_tag+"[" + this.GetInstanceID().ToString("X")
				+ "][" + Time.time.ToString("0.0000") + "]: OnDestroy");
		}
	}
}

