#include "sfe_bus.h"

/// @brief Constructor
/// @param addr Address of the device
/// @param port Wire port chosen to be used for I2C transactions
/// @return Error code
int32_t SFE_BusI2C::init(uint8_t addr, TwoWire& port)
{
    devAddr = addr;
    devPort = &port;

    return 0;
}

/// @brief Reads a register at the requested address for the requested 
///  number of bytes.
/// @param regAddress Register address
/// @param dataBuffer Data buffer
/// @param numBytes Number of bytes requested from register address
/// @return Error code (true for success, )
int32_t SFE_BusI2C::readRegs(uint8_t regAddress, uint8_t* dataBuffer, uint8_t numBytes)
{
    // Jump to desired register address
    devPort->beginTransmission(devAddr);
    devPort->write(regAddress);
    if(devPort->endTransmission())
    {
        return 0;
    }

    // Read bytes from these registers
    devPort->requestFrom(devAddr, numBytes);

    // Store all requested bytes
    for(uint32_t i = 0; i < numBytes && devPort->available(); i++)
    {
        dataBuffer[i] = devPort->read();
    }

    return 1;
}

/// @brief Writes to the devices register
/// @param regAddress Register address 
/// @param dataBuffer Data buffer
/// @param numBytes Number of bytes requested from register address
/// @return Error code (false for error, true for success)
int32_t SFE_BusI2C::writeRegs(uint8_t regAddress, const uint8_t* dataBuffer, uint8_t numBytes)
{
    // Begin transmission
    devPort->beginTransmission(devAddr);

    // Write the address
    devPort->write(regAddress);
    
    // Write all the data
    for(uint32_t i = 0; i < numBytes; i++)
    {
        devPort->write(dataBuffer[i]);
    }

    // End transmission
    if(devPort->endTransmission())
    {
        return false;
    }

    return true;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SPI Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief This function containts the methods to init/setup this device. The caller can provide
///  a SPI port, or this class will use the default.
/// @param spiPort SPI port chosen by user
/// @param ismSPISettings SPI settings for every transaction
/// @param cs Chip Select Pin 
/// @param bInit True or false for initialization
/// @return Error code
int32_t SFE_BusSPI::init(uint8_t cs, SPIClass& spiPort, bool bInit)
{
    // if we don't have a SPI port already
    if( !_spiPort )
    {
        _spiPort = &spiPort;

        if( bInit )
            _spiPort->begin();
    }

		// SPI settings are needed for every transaction
		_sfeSPISettings = SPISettings(1000000, MSBFIRST, SPI_MODE0);

		// The chip select pin can vary from platform to platform and project to project
		// and so it must be given by the user. 
		if( !cs )
			return 0; 
		
		_cs = cs;

    return 1;
}

/// @brief This function writes a block of data to a device
/// @param i2c_address Address to write to 
/// @param offset Offset of register
/// @param data Data to write to register
/// @param length Length of data to be written to register
/// @return Error code
int32_t SFE_BusSPI::writeRegisterRegion(uint8_t offset, const uint8_t *data, uint16_t length)
{
		int i;

		// Apply settings
    _spiPort->beginTransaction(_sfeSPISettings);
		// Signal communication start
		digitalWrite(_cs, LOW);
    _spiPort->transfer(offset);

		for(i = 0; i < length; i++)
		{
			_spiPort->transfer(*data++);
		}

		// End communication
		digitalWrite(_cs, HIGH);
    _spiPort->endTransaction();
		return 0; 
}

/// @brief This function reads a block of data from the register on the device.
/// @param addr Address chosing to read from
/// @param reg Register
/// @param data Data to be filled
/// @param numBytes Number of bytes to read from
/// @return Returns the data from the register desired to read from.
int32_t SFE_BusSPI::readRegisterRegion(uint8_t reg, uint8_t *data, uint16_t numBytes)
{
    if (!_spiPort)
        return -1;

    int i; // counter in loop

		// Apply settings
    _spiPort->beginTransaction(_sfeSPISettings);
		// Signal communication start
		digitalWrite(_cs, LOW);
		// A leading "1" must be added to transfer with register to indicate a "read"
		reg = (reg | SPI_READ);
    _spiPort->transfer(reg);

		for(i = 0; i < numBytes; i++)
		{
			*data++ = _spiPort->transfer(0x00);
		}

		// End transaction
		digitalWrite(_cs, HIGH);
    _spiPort->endTransaction();
		return 0; 

}