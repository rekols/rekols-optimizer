/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 Rekols
 *
 * Author:     Rekols <rekols@foxmail.com>
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "home_widget.h"
#include "utils.h"

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    bottomLayout = new QHBoxLayout();
    infoLayout = new QVBoxLayout();
    networkLayout = new QVBoxLayout();
    systemInfo = new QLabel("SYSTEM INFO");
    hostName = new QLabel("Hostname: ");
    platform = new QLabel("Platform: ");
    distribution = new QLabel("Distribution: ");
    kernel = new QLabel("Kernel Release: ");
    cpuModel = new QLabel("Cpu Model: ");
    cpuCoreCount = new QLabel("Cpu Core: ");

    uploadInfo = new QLabel("UPLOAD");
    downloadInfo = new QLabel("DOWNLOAD");
    uploadLabel = new QLabel("↑ 0.0 B/s");
    downloadLabel = new QLabel("↓ 0.0 B/s");

    thread = new Thread();
    monitorWidget = new MonitorWidget();
    cpuMonitor = new CPUMonitor();
    memoryMonitor = new MemoryMonitor();
    diskMonitor = new DiskMonitor();

    systemInfo->setStyleSheet("QLabel { color: #4088C6 }");
    uploadInfo->setStyleSheet("QLabel { color: #31A38C }");
    downloadInfo->setStyleSheet("QLabel { color: #C45045 }");
    hostName->setStyleSheet("QLabel { color: #505050 }");
    platform->setStyleSheet("QLabel { color: #505050 }");
    distribution->setStyleSheet("QLabel { color: #505050 }");
    kernel->setStyleSheet("QLabel { color: #505050 }");
    cpuModel->setStyleSheet("QLabel { color: #505050 }");
    cpuCoreCount->setStyleSheet("QLabel { color: #505050 }");
    uploadLabel->setStyleSheet("QLabel { color: #505050 }");
    downloadLabel->setStyleSheet("QLabel { color: #505050 }");

    QFont font;
    font.setPointSize(18);
    systemInfo->setFont(font);
    uploadInfo->setFont(font);
    downloadInfo->setFont(font);

    monitorWidget->layout->addSpacing(15);
    monitorWidget->layout->addWidget(cpuMonitor);
    monitorWidget->layout->addWidget(memoryMonitor);
    monitorWidget->layout->addWidget(diskMonitor);
    monitorWidget->layout->addSpacing(15);

    bottomLayout->addSpacing(25);
    bottomLayout->addLayout(infoLayout);
    bottomLayout->addLayout(networkLayout);
    bottomLayout->addSpacing(25);

    infoLayout->addStretch();
    infoLayout->addWidget(systemInfo);
    infoLayout->addWidget(hostName);
    infoLayout->addWidget(platform);
    infoLayout->addWidget(distribution);
    infoLayout->addWidget(kernel);
    infoLayout->addWidget(cpuModel);
    infoLayout->addWidget(cpuCoreCount);
    infoLayout->addStretch();

    networkLayout->addWidget(uploadInfo);
    networkLayout->addWidget(uploadLabel);
    networkLayout->addSpacing(20);
    networkLayout->addWidget(downloadInfo);
    networkLayout->addWidget(downloadLabel);
    networkLayout->addStretch();

    layout->addWidget(monitorWidget);
    layout->addStretch();
    layout->addLayout(bottomLayout);
    layout->addStretch();

    hostName->setText("HostName: " + Utils::getUserName());
    platform->setText("Platform: " + Utils::getPlatform());
    distribution->setText("Distribution: " + Utils::getDistribution());
    kernel->setText("Kernel Release: " + Utils::getKernel());
    cpuModel->setText("Cpu Model: " + Utils::getCpuModel());
    cpuCoreCount->setText("Cpu Core: " + Utils::getCpuCoreCount());

    thread->start();

    connect(thread, &Thread::updateCpuPercent, this, &HomeWidget::updateCpuPercent);
    connect(thread, &Thread::updateMemoryPercent, this, &HomeWidget::updateMemoryPercent);
    connect(thread, &Thread::updateMemory, this, &HomeWidget::updateMemory);
    connect(thread, &Thread::updateDiskPercent, this, &HomeWidget::updateDiskPercent);
    connect(thread, &Thread::updateDisk, this, &HomeWidget::updateDisk);
    connect(thread, &Thread::updateNetworkSpeed, this, &HomeWidget::updateNetworkSpeed);
}

void HomeWidget::updateCpuPercent(int cpuPercent)
{
    cpuMonitor->setPercentValue(cpuPercent);
}

void HomeWidget::updateMemoryPercent(int memoryPercent)
{
    memoryMonitor->setPercentValue(memoryPercent);
}

void HomeWidget::updateMemory(QString memory)
{
    memoryMonitor->setMemoryInfo(memory);
}

void HomeWidget::updateDiskPercent(int diskPercent)
{
    diskMonitor->setPercentValue(diskPercent);
}

void HomeWidget::updateDisk(QString disk)
{
    diskMonitor->setDiskInfo(disk);
}

void HomeWidget::updateNetworkSpeed(QString upload, QString download)
{
    uploadLabel->setText(upload);
    downloadLabel->setText(download);
}