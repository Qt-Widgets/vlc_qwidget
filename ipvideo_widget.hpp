/*
 * Copyright (c) 2015, Alireza Hosseini.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file QRRIpVideoWidget.h
 * @brief Ip Video Widget.
 * @see QRRIpVideoWidget
 * @author Alireza Hosseini
 */
#ifndef IPVIDEO_WIDGET_H
#define IPVIDEO_WIDGET_H

#include <QtNetwork>
#include "vlc/vlc.h"
#include <QtGui>


//preparation of the vlc command
const char * const vlc_args[] = {"--no-autoscale"
          //"-I", "dummy", /* Don't use any interface */
          //"--ignore-config", /* Don't use VLC's config */
          //"--extraintf=logger", //log anything
          //"--verbose=2", //be much more verbose then normal for debugging purpose
                                };


class IpVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IpVideoWidget(QWidget *input_parent,QString input_stream_url);
    /*NOTICE: for best functionallity of widget call init function after setting parent of widget*/
    /*Unhandlable bug!(related to libvlc)*/
    bool initializeCamera();

    Q_SLOT bool refresh();

    void  updateURL(QString new_url);

    void releaseCamera();


private:

    libvlc_instance_t     *vlc_instance_;
    libvlc_media_player_t *vlc_media_player_;
    libvlc_media_t        *vlc_media_;
    QString                stream_url_;
    QWidget               *parent_widget_;
};

#endif // QRRIPCAMERAWIDGET_H
