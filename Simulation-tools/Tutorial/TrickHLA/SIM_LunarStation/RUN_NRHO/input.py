# configure Trick
trick.frame_log_on()
trick.real_time_enable()
trick.exec_set_software_frame(0.1)
trick.itimer_enable()
trick.exec_set_enable_freeze(True)
trick.exec_set_freeze_command(True)
trick.sim_control_panel_set_enabled(True)
trick.sim_services.exec_set_trap_sigfpe(1)
trick.sim_services.exec_set_terminate_time(3600*24.0*7.0) # Run for 7 days

# call the common input file to setup the time
f = "Modified_data/common.py"
exec(compile(open(f, 'rb').read(), f, 'exec'), globals(), locals())

################# Set lunar station initial state for NRHO #####################
# NRHO state vector was obtained from JPL WebGeocalc https://wgc.jpl.nasa.gov:8443/webgeocalc/#StateVector
# Kernel: misc/MORE_PROJECTS/DSG/receding_horiz_3189_1burnApo_DiffCorr_15yr.bsp
# Target body ID: -60000
# Observer name: Moon
# Reference Frame: J2000
# Time: UTC 2022 Nov 30 00:00:00.0
# Position = [-4975.32454464, -5553.35729025, -9421.80746280] km
# Velocity = [0.18957887, -0.04297009, 0.82347148] km/s
lunar_station.trans_init.set_subject_body(lunar_station.dyn_body)
lunar_station.trans_init.reference_ref_frame_name = "Moon.inertial"
lunar_station.trans_init.body_frame_id            = "composite_body"
lunar_station.trans_init.position                 = trick.attach_units( "km",[-4975.32454464, -5553.35729025, -9421.80746280])
lunar_station.trans_init.velocity                 = trick.attach_units( "km/s",[0.18957887, -0.04297009, 0.82347148])
lunar_station.rot_init.set_subject_body(lunar_station.dyn_body)
lunar_station.rot_init.action_name                = "lunar_station_rot_init"
lunar_station.rot_init.reference_ref_frame_name   = "Moon.inertial"
lunar_station.rot_init.body_frame_id              = "composite_body"
lunar_station.rot_init.orientation.data_source    = trick.Orientation.InputEulerRotation
lunar_station.rot_init.orientation.euler_sequence = trick.Orientation.Yaw_Pitch_Roll
lunar_station.rot_init.orientation.euler_angles   = trick.attach_units( "degree",[ 0.0, 0.0, 0.0])
lunar_station.rot_init.ang_velocity               = trick.attach_units( "degree/s",[ 0.0, 0.0, 0.0])

# Log vehicle state
exec(open( "Log_data/log_lunar_station_state.py").read())
log_sv_state_rec(60.0, "LunarStation")
