class Configuration {
private:
	uint8_t pwm = 0;
	uint8_t gas_follow_up_time = 0; // gasnachlaufzeit
	uint8_t gas_lead_time = 0;      // gasvorlaufzeit

public:
	void Save();
	void Load();

	void SetPWM(uint8_t p) { this->pwm = p; };
	uint8_t GetPWM() { return this->pwm; };

	void SetGasFollowUpTime(uint8_t f) { this->gas_follow_up_time = f; };
	uint8_t GetGasFollowUpTime() { return this->gas_follow_up_time; };

	void SetGasLeadTime(uint8_t l) { this->gas_lead_time = l; };
	uint8_t GetGasLeadTime() { return this->gas_lead_time; };
};
