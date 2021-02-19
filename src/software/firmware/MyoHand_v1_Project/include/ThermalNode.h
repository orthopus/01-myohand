#ifndef THERMALNODE_H
#define THERMALNODE_H

/* --- ThermalNode Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provides tools to calculate the temperature
and its evolution on a node.
*/

class ThermalNode
{

private:
  const float sample_period;
  const float tau_inverse;
  const float R_th;
  float current_temp;
  float prev_temp;

  const float R_mot;
  const float T_ext;

public:
  ThermalNode(float period, float tau, float Rth, float temp_init, float Rmot = 0.0, float Text = 0.0);
  float update_temp(float current, const ThermalNode &neighboor_down, bool nbr_down_updated = false);
  float update_temp(const ThermalNode &neighboor_up, const ThermalNode &neighboor_down, bool nbr_up_updated = false, bool nbr_down_updated = false);
  float update_temp(const ThermalNode &neighboor_up, bool nbr_up_updated = false);

  static float getDeltaTemp(const ThermalNode &tn1, const ThermalNode &tn2);
  float getTemp();
  float getPrevTemp();
};

#endif
