
/*******************************************************************************
* Copyright (c) 2018 Elhay Rauper
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
*     * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/


#include "MilliStopper.h"

MilliStopper::MilliStopper() {state_ = State::STOPPED;}

/* start stopper. if already started, do nothing */
void MilliStopper::start()
{
    if (state_ == State::STOPPED)
    {
        start_time_ = millis();
        end_time_ = 0;
        state_ = State::STARTED;
    }
}

/* override original start time, and start stopper again */
void MilliStopper::startOver() 
{
    start_time_ = millis();
    if (state_ == State::STOPPED)
        state_ = State::STARTED;
}

void MilliStopper::pause()
{
    if (state_ == State::STARTED)
    {
        end_time_ = millis();
        state_ = State::PAUSED;
    }
}

void MilliStopper::resume()
{
    if (state_ == State::PAUSED)
        state_ = State::STARTED;
}

void MilliStopper::stop()
{
    if (state_ != State::STOPPED)
    {
        end_time_ = millis();
        state_ = State::STOPPED;
    }
}

// if stopper is still running, return elapsed
// time b/w call time and start time. else, if 
// stopper is paused or stopped, return elpased
// time b/w end_time_ and start_time_
unsigned long MilliStopper::getElapsedTime()
{
    if (state_ == State::STARTED)
        return millis() - start_time_;
    else
        return end_time_ - start_time_;
}
