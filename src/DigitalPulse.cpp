#include "DigitalPulse.h"

DigitalPulse::DigitalPulse() :
  m_pin(1),
  m_delay(0),
  m_uptime(500),
  m_downtime(500),
  m_cycles(1),
  m_state(PulseState::STATE_IDLE),
  m_stateHistory(PulseState::STATE_IDLE),
  m_cycleIndex(0),
  m_timeout(0),
  m_timestamp(0)
{

}


uint32_t DigitalPulse::duration()
{
  return m_delay + m_cycles * (m_uptime + m_downtime);
}


void DigitalPulse::start()
{
  // can't start running pulse
  if (m_state != PulseState::STATE_IDLE)
    return;

  // trigger pulse
  m_state = PulseState::STATE_DELAY;
  m_stateHistory = m_state;
  m_cycleIndex = 0;
  m_timeout = m_delay;
  m_timestamp = millis();
}


void DigitalPulse::stop()
{
  m_state = PulseState::STATE_IDLE;
  m_stateHistory = m_state;
  m_cycleIndex = 0;
  m_timeout = 0;
  m_timestamp = 0;
}


void DigitalPulse::resume()
{
  m_state = m_stateHistory;
  m_timestamp = millis();
}


void DigitalPulse::pause()
{
  m_state = PulseState::STATE_IDLE;
}


void DigitalPulse::update()
{
  // skip update if pulse is idle
  if (m_state == PulseState::STATE_IDLE)
    return;

  // check if edge is reached
  if (millis() - m_timestamp >= m_timeout)
  {
    // update state
    m_state++;

    // rewind if period is reached
    if (m_state == PulseState::STATE_PERIOD)
    {
      m_cycleIndex++;
      // exit if cycles are reached
      if (m_cycleIndex == m_cycles)
      {
        stop();
        return;
      }
      m_state = PulseState::STATE_UPTIME;
    }


    // update timeout based on current state
    if (m_state == PulseState::STATE_UPTIME)
    {
      m_timeout = m_uptime;
    }
    else if (m_state == PulseState::STATE_DOWNTIME)
    {
      m_timeout = m_downtime;
    }

    // update history state
    m_stateHistory = m_state;

    // update timestamp
    m_timestamp = millis();
  }
}
