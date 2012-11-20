/**
 * \file TcpSocketRxComponent.h
 * \version 1.0
 *
 * \section COPYRIGHT
 *
 * Copyright 2012 The Iris Project Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution
 * and at http://www.softwareradiosystems.com/iris/copyright.html.
 *
 * \section LICENSE
 *
 * This file is part of the Iris Project.
 *
 * Iris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Iris is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * A copy of the GNU Lesser General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 * \section DESCRIPTION
 *
 * A source component which listens to a TCP socket.
 */

#ifndef TCPSOCKETRXCOMPONENT_H_
#define TCPSOCKETRXCOMPONENT_H_

#include "irisapi/PNComponent.h"

//For boost asio sockets
#include <boost/asio.hpp>

namespace iris
{

/*!
 * \brief A TCP socket receiver
 *
 * The TcpSocketRxComponent receives data from a TCP socket.
 */
class TcpSocketRxComponent: public PNComponent
{
private:
	//! Port number to bind to
  unsigned short port_x;
  //! Size of buffers to be generated
  unsigned int bufferSize_x;
  //! Data type of output
  std::string outputType_x;

  //! The ID of the output data type
  int outputTypeId_;

  boost::asio::io_service ioService_;
  boost::asio::ip::tcp::socket* socket_;
  boost::asio::ip::tcp::acceptor* acceptor_;

  char* buffer_;
  bool connected_;

  template<typename T> void writeOutput();
public:
	/*!
	 * Call the constructor on PNComponent and pass in all details
	 * about the component.	Register all parameters and events.
	 * \param name the name given to this component in the radio config
	 */
  TcpSocketRxComponent(std::string name);

	/*!
	 * Destructor - clean up
	 */
	~TcpSocketRxComponent();

	/*!
	 * Given the data-types associated with each input port, provide
	 * the data-types which will be produced on each output port.
	 * \param inputTypes the map of input port names and data-type identifiers
	 * \return map of output port names and data-type identifiers
	 */
  virtual std::map<std::string, int> calculateOutputTypes(std::map<std::string, int> inputTypes);

  /*!
	 * Register the input and output ports of this component
	 * by declaring them as input or output, naming them and
	 * providing a list of valid data types.
	 */
  virtual void registerPorts();

  /*!
	 * Do any initialization required by this component.
	 */
  virtual void initialize();

  /*!
   * Start this IO component
   */
  virtual void start();

  /*!
   	 * This is where the work of this component gets done.
   	 * Typically components will take DataSets from their input
   	 * ports, process them and write DataSets to their output ports.
   	 */
  virtual void process();

  /*!
	 * Stop this IO component
	 */
  virtual void stop();
};

} /* namespace iris */

#endif /* TCPSOCKETRXCOMPONENT_H_ */
