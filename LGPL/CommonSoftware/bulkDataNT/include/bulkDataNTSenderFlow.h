#ifndef _BULK_DATA_NT_SENDER_FLOW_H_
#define _BULK_DATA_NT_SENDER_FLOW_H_
/*******************************************************************************
* ALMA - Atacama Large Millimiter Array
* (c) European Southern Observatory, 2011
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*
* "@(#) $Id: bulkDataNTSenderFlow.h,v 1.14 2012/01/11 11:48:30 bjeram Exp $"
*
* who       when      what
* --------  --------  ----------------------------------------------
* bjeram  2011-04-19  created
*/

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif

#include "bulkDataNTFlow.h"
#include "bulkDataNTDDSPublisher.h"
#include "bulkDataNTSenderStream.h"
#include "bulkDataNTWriterListener.h"


namespace AcsBulkdata
{

class BulkDataNTSenderStream;

class BulkDataNTSenderFlow : public BulkDataNTFlow
{
public:

	/**
	 * Constructor
	 */
	BulkDataNTSenderFlow(BulkDataNTSenderStream *senderStream,
						const char* flowName,
						const SenderFlowConfiguration &sndCfg
						/*cb*/);

	/**
	 * Destructor
	 */
	virtual ~BulkDataNTSenderFlow();


	/**
	 * Returns number of connected receivers for the flow.
	 * @return nmumber of receivers
	 */
	unsigned int getNumberOfReceivers();

	/**
	 *
	 * @param param  parameter data
	 * @param len parameter data length
	 * @exception #StartSendErrorExImpl
	 */
	/**
	 * Deprecated method to send "START" and parameter using #ACE_Message_Block
	 * @deprecated
	 * @param param parameter in form of #ACE_Message_Block
	 */
	void startSend(ACE_Message_Block *param = 0);

	/**
	 * Method to send "START" and parameter
	 * @param param  parameter data
	 * @param len parameter data length
	 * @exception #StartSendErrorExImpl
	 */
	void startSend(const unsigned char *param, size_t len);

	/**
	 * Method to send data. The data length can be of any size.
	 * @param buffer  data
	 * @param len length of data
	 * @exception #SendDataErrorExImpl
	 */
	void sendData(const unsigned char *buffer, size_t len);

	/**
	 * Method to send "stop"
	 * @exception #StopSendErrorExImpl
	 */
	void stopSend();

protected:
	AcsBulkdata::BulkDataNTSenderStream *senderStream_m;

	AcsBulkdata::BulkDataNTDDSPublisher *ddsPublisher_m;
	DDS::Topic *ddsTopic_m;
	BulkDataNTWriterListener *writerReaderListener_m;
	ACSBulkData::BulkDataNTFrameDataWriter *ddsDataWriter_m;

	DDS::Duration_t ackTimeout_m;  /// ACKs timeout
	void setACKsTimeout(double ACKsTimeout);  /// setter fro ackTimeout


	// should it go to upper class Publisher ?
	/**
	 * Common method to send frame(s) to the topic. The method it is used internally by:
	 * #startSend, #sendData and #stopSend
	 * @param dataType data frame type (START/DATA/STOP)
	 * @param param   - data
	 * @param len length of data
	 * @param restFrameCount how many frames do we have still sent
	 * @exception #SendFrameTimeoutExImpl, #SendFrameGenericErrorExImpl, #FrameAckTimeoutExImpl
	 */
	void writeFrame(ACSBulkData::DataType dataType,  const unsigned char *param=0, size_t len=0, unsigned int restFrameCount=0);

	// frame
	ACSBulkData::BulkDataNTFrame *frame_m;

	/// disable default - empty constructor
	BulkDataNTSenderFlow();
	/// ALMA C++ coding standards state assignment operators should be disabled.
	void operator=(const BulkDataNTSenderFlow&);
	/// ALMA C++ coding standards state copy constructors should be disabled.
	BulkDataNTSenderFlow(const BulkDataNTSenderFlow&);
};//class BulkDataSenderFlow

};


#endif /*!_H*/
