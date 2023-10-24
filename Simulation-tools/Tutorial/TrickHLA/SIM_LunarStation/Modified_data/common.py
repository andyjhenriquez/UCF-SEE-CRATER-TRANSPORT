###############################################################################
# Setup JEOD time.
# This tells JEOD how to initialize and update the time model
###############################################################################
jeod_time.time_manager_init.initializer = "UTC"
jeod_time.time_manager_init.sim_start_format = trick.TimeEnum.calendar

jeod_time.time_tai.initialize_from_name = "UTC"
jeod_time.time_ut1.initialize_from_name = "TAI"
jeod_time.time_tt.initialize_from_name  = "TAI"
jeod_time.time_gmst.initialize_from_name  = "UT1"

jeod_time.time_tai.update_from_name = "Dyn"
jeod_time.time_ut1.update_from_name = "TAI"
jeod_time.time_utc.update_from_name = "TAI"
jeod_time.time_tt.update_from_name  = "TAI"
jeod_time.time_gmst.update_from_name  = "UT1"

jeod_time.time_utc.true_utc = False
jeod_time.time_ut1.true_ut1 = False

# uses UTC to set the initial time
jeod_time.time_utc.calendar_year   = 2022
jeod_time.time_utc.calendar_month  = 11
jeod_time.time_utc.calendar_day    = 30
jeod_time.time_utc.calendar_hour   = 0
jeod_time.time_utc.calendar_minute = 0
jeod_time.time_utc.calendar_second = 0

###############################################################################
# Setup JEOD Environment
###############################################################################
dynamics.dyn_manager_init.sim_integ_opt = trick.sim_services.Runge_Kutta_4
dynamics.dyn_manager.deriv_ephem_update = False

###############################################################################
# Configure vehicle integration information
###############################################################################
lunar_station.dyn_body.set_name( "LunarStation" )
lunar_station.dyn_body.integ_frame_name = "Moon.inertial"
lunar_station.dyn_body.translational_dynamics = True
lunar_station.dyn_body.rotational_dynamics = True

###############################################################################
# Set lunar station mass properties
###############################################################################
lunar_station.mass_init.set_subject_body(lunar_station.dyn_body.mass)
lunar_station.mass_init.properties.pt_orientation.data_source =    trick.Orientation.InputEigenRotation
lunar_station.mass_init.properties.pt_orientation.eigen_angle = 0.0
lunar_station.mass_init.properties.pt_orientation.eigen_axis  = [ 0.0, 1.0, 0.0]
lunar_station.mass_init.properties.position    = [ 0.0, 0.0, 0.0]
lunar_station.mass_init.properties.inertia[0]  = [ 1.0e5, 0.0,   0.0  ]     #(kg*m2)
lunar_station.mass_init.properties.inertia[1]  = [ 0.0,   1.0e5, 0.0  ]     #(kg*m2)
lunar_station.mass_init.properties.inertia[2]  = [ 0.0,   0.0,   1.0e5]     #(kg*m2)
lunar_station.mass_init.properties.mass        = 10000  # (kg)

###############################################################################
# Set lunar station gravity controls
###############################################################################
lunar_station.earth_grav_control.source_name = "Earth"
lunar_station.earth_grav_control.active      = True
lunar_station.earth_grav_control.spherical   = True
lunar_station.earth_grav_control.gradient    = False

lunar_station.moon_grav_control.source_name = "Moon"
lunar_station.moon_grav_control.active      = True
lunar_station.moon_grav_control.spherical   = True
lunar_station.moon_grav_control.gradient    = False

lunar_station.dyn_body.grav_interaction.add_control(lunar_station.earth_grav_control)
lunar_station.dyn_body.grav_interaction.add_control(lunar_station.moon_grav_control)

###############################################################################
# Set body action to initialize lunar station mass and state
###############################################################################
dynamics.dyn_manager.add_body_action(lunar_station.mass_init)
dynamics.dyn_manager.add_body_action(lunar_station.trans_init)
dynamics.dyn_manager.add_body_action(lunar_station.rot_init)
