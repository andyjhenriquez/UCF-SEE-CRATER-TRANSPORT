# configure Trick
trick.frame_log_on()
trick.real_time_enable()
trick.exec_set_software_frame(0.1)
trick.itimer_enable()
trick.exec_set_enable_freeze(True)
trick.exec_set_freeze_command(True)
trick.sim_control_panel_set_enabled(True)
trick.sim_services.exec_set_trap_sigfpe(1)
trick.sim_services.exec_set_terminate_time(3600*2.0) # Run for 2 hours

# call the common input file to setup the time
f = "Modified_data/common.py"
exec(compile(open(f, 'rb').read(), f, 'exec'), globals(), locals())

# Set lunar station initial state for polar orbit 
lunar_station.trans_init.set_subject_body(lunar_station.dyn_body)
lunar_station.trans_init.reference_ref_frame_name = "Moon.inertial"
lunar_station.trans_init.body_frame_id            = "composite_body"
lunar_station.trans_init.position                 = trick.attach_units( "km",[2000, 0.0, 0.0])
lunar_station.trans_init.velocity                 = trick.attach_units( "km/s",[0.0, 0.0, 1.565695])
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
log_sv_state_rec(1.0, "LunarStation")
