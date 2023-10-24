def log_sv_state_rec ( log_cycle , VEH_NAME  ) :
  recording_group_name =  ""+VEH_NAME+"_State"
  dr_group = trick.sim_services.DRAscii(recording_group_name)
  dr_group.thisown = 0
  dr_group.set_cycle(log_cycle)
  dr_group.freq = trick.sim_services.DR_Always

  dr_group.add_variable( " jeod_time.time_utc.seconds ")
  for ii in range(0,3) :
    dr_group.add_variable( "lunar_station.dyn_body.composite_body.state.trans.position[" + str(ii) + "]" )

  for ii in range(0,3) :
    dr_group.add_variable( "lunar_station.dyn_body.composite_body.state.trans.velocity[" + str(ii) + "]" )

  for ii in range(0,3) :
    dr_group.add_variable( "lunar_station.dyn_body.derivs.trans_accel[" + str(ii) + "]" )

  trick.add_data_record_group(dr_group)
  return
