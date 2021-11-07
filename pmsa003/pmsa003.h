#ifndef PMSA003_PMSA003_H_
#define PMSA003_PMSA003_H_

typedef enum
{
	ACTIVE = 0,
	PASSIVE,
} PMSAModeType;

typedef enum
{
	START_CHAR_NOT_FOUND = 0,
	CHECKSUM_ERROR,
	RECEIVED_SUCCES,
} PMSAStateType;

typedef struct
{
	PMSAModeType mode;
	// Standard Particles, CF=1
	uint16_t PM1_0_SP;
	uint16_t PM2_5_SP;
	uint16_t PM10_0_SP;
	// Atmospheric environment
	uint16_t PM1_0_AE;
	uint16_t PM2_5_AE;
	uint16_t PM10_0_AE;
	// Number of particles with diameter beyond {_x_x}um in 0.1L of air
	uint16_t particles_0_3um;
	uint16_t particles_0_5um;
	uint16_t particles_1_0um;
	uint16_t particles_2_5um;
	uint16_t particles_5_0um;
	uint16_t particles_10_0um;
	// Check code=Start character1 + Start character2 + ... + data13
	uint16_t checksum;
} PMSASensorType;

void PMSA_Init(PMSASensorType *pmsa);
void PMSA_Sleep();
void PMSA_WakeUp();
void PMSA_ActiveMode(PMSASensorType *pmsa);
void PMSA_PassiveMode(PMSASensorType *pmsa);
void PMSA_RequestRead(PMSASensorType *pmsa);
PMSAStateType PMSA_Read(PMSASensorType *pmsa, uint8_t *buff, uint8_t size);

#endif /* PMSA003_PMSA003_H_ */
