#include "ThermalNode.h"

ThermalNode::ThermalNode(float period, float tau, float Rth, float temp_init,
                         float Rmot = 0.0, float Text = 0.0)
    : sample_period{period}, tau_inverse{1.0 / tau}, R_th{Rth},
      current_temp{temp_init}, prev_temp{temp_init}, R_mot{Rmot}, T_ext{Text} {}

float ThermalNode::update_temp(float current, const ThermalNode &neighboor_down,
                               bool nbr_down_updated = false) {
  prev_temp = current_temp;
  float nbr_down_prev_value = (nbr_down_updated) ? neighboor_down.current_temp
                                                 : neighboor_down.prev_temp;

  float dT = current * current * (R_mot * (R_th * tau_inverse)) -
             (prev_temp - nbr_down_prev_value) * tau_inverse;
  current_temp = prev_temp + dT * sample_period;
  return dT;
}

float ThermalNode::update_temp(const ThermalNode &neighboor_up,
                               const ThermalNode &neighboor_down,
                               bool nbr_up_updated = false,
                               bool nbr_down_updated = false) {
  prev_temp = current_temp;
  float nbr_up_prev_value =
      (nbr_up_updated) ? neighboor_up.current_temp : neighboor_up.prev_temp;
  float nbr_down_prev_value = (nbr_down_updated) ? neighboor_down.current_temp
                                                 : neighboor_down.prev_temp;

  float dT = ((R_th * tau_inverse) / neighboor_up.R_th) *
                 (nbr_up_prev_value - prev_temp) -
             (prev_temp - nbr_down_prev_value) * tau_inverse;
  current_temp = prev_temp + dT * sample_period;
  return dT;
}
float ThermalNode::update_temp(const ThermalNode &neighboor_up,
                               bool nbr_up_updated = false) {
  prev_temp = current_temp;
  float nbr_up_prev_value =
      (nbr_up_updated) ? neighboor_up.current_temp : neighboor_up.prev_temp;

  float dT = ((R_th * tau_inverse) / neighboor_up.R_th) *
                 (nbr_up_prev_value - prev_temp) -
             (prev_temp - T_ext) * tau_inverse;
  current_temp = prev_temp + dT * sample_period;
  return dT;
}

static float ThermalNode::getDeltaTemp(const ThermalNode &tn1,
                                       const ThermalNode &tn2) {
  return (tn1.current_temp - tn2.current_temp);
}

float ThermalNode::getTemp() { return current_temp; }
float ThermalNode::getPrevTemp() { return prev_temp; }
