#include "sfe_bus.h"

/// @brief Constructor
/// @param addr 
/// @param port 
/// @return Error code
bool SFE_BusI2C::init(uint8_t addr, TwoWire& port)
{
    devAddr = addr;
    devPort = &port;

    return false;
}

/// @brief Reads a register at the requested address for the requested 
///  number of bytes.
/// @param regAddress Register address
/// @param dataBuffer Data buffer
/// @param numBytes Number of bytes requested from register address
/// @return Error code (true for success, )
bool SFE_BusI2C::readRegs(uint8_t regAddress, uint8_t* dataBuffer, uint8_t numBytes)
{
    // Jump to desired register address
    devPort->beginTransmission(devAddr);
    devPort->write(regAddress);
    if(devPort->endTransmission())
    {
        return false;
    }

    // Read bytes from these registers
    devPort->requestFrom(devAddr, numBytes);

    // Store all requested bytes
    for(uint32_t i = 0; i < numBytes && devPort->available(); i++)
    {
        dataBuffer[i] = devPort->read();
    }

    return true;
}

/// @brief Writes to the devices register
/// @param regAddress Register address 
/// @param dataBuffer Data buffer
/// @param numBytes Number of bytes requested from register address
/// @return Error code (false for error, true for success)
bool SFE_BusI2C::writeRegs(uint8_t regAddress, const uint8_t* dataBuffer, uint8_t numBytes)
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
/// @return 
bool SfeSPI::init(SPIClass &spiPort, SPISettings& ismSPISettings, uint8_t cs,  bool bInit)
{

    // if we don't have a SPI port already
    if( !_spiPort )
    {
        _spiPort = &spiPort;

        if( bInit )
            _spiPort->begin();
    }


		// SPI settings are needed for every transaction
		_sfeSPISettings = ismSPISettings; 

		// The chip select pin can vary from platform to platform and project to project
		// and so it must be given by the user. 
		if( !cs )
			return false; 
		
		_cs = cs;

    return true;
}

/// @brief This function contains the methods to init/setup this device. 
/// @param cs Chip Select
/// @param bInit Initialize
/// @return Returns an error code (false no error, true error)
bool SfeSPI::init(uint8_t cs,  bool bInit)
{

		//If the transaction settings are not provided by the user they are built here.
		SPISettings spiSettings = SPISettings(3000000, MSBFIRST, SPI_MODE3); 

		//In addition of the port is not provided by the user, it defaults to SPI here. 
		return init(SPI, spiSettings, cs, bInit);

}

/// @brief This function writes a byte to a chosen register
/// @param i2c_address Address to write to
/// @param offset Offset of regsiter
/// @param dataToWrite Data to write to register
/// @return Returns true if byte written, false otherwise 
bool SfeSPI::writeRegisterByte(uint8_t i2c_address, uint8_t offset, uint8_t dataToWrite)
{

    if( !_spiPort )
        return false;

		// Apply settings
    _spiPort->beginTransaction(_sfeSPISettings);
		// Signal communication start
		digitalWrite(_cs, LOW);

    _spiPort->transfer(offset);
    _spiPort->transfer(dataToWrite);

		// End communcation
		digitalWrite(_cs, HIGH);
    _spiPort->endTransaction();

		return true;
}

/// @brief This function writes a block of data to a device
/// @param i2c_address Address to write to 
/// @param offset Offset of register
/// @param data Data to write to register
/// @param length Length of data to be written to register
/// @return Error code
int SfeSPI::writeRegisterRegion(uint8_t i2c_address, uint8_t offset, const uint8_t *data, uint16_t length)
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
int SfeSPI::readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes)
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