/**************************************************************************//**
 * @file     mpu_armv7.h
 * @brief    CMSIS MPU API for ARMv7 MPU
 * @version  V5.0.2
 * @date     09. June 2017
 ******************************************************************************/
/*
 * Copyright (c) 2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef MPU_ARMV7_H
#define MPU_ARMV7_H

#define MPU_REGION_SIZE_32B      ((uint8_t)0x04U)
#define MPU_REGION_SIZE_64B      ((uint8_t)0x05U)
#define MPU_REGION_SIZE_128B     ((uint8_t)0x06U)
#define MPU_REGION_SIZE_256B     ((uint8_t)0x07U)
#define MPU_REGION_SIZE_512B     ((uint8_t)0x08U)
#define MPU_REGION_SIZE_1KB      ((uint8_t)0x09U)
#define MPU_REGION_SIZE_2KB      ((uint8_t)0x0AU)
#define MPU_REGION_SIZE_4KB      ((uint8_t)0x0BU)
#define MPU_REGION_SIZE_8KB      ((uint8_t)0x0CU)
#define MPU_REGION_SIZE_16KB     ((uint8_t)0x0DU)
#define MPU_REGION_SIZE_32KB     ((uint8_t)0x0EU)
#define MPU_REGION_SIZE_64KB     ((uint8_t)0x0FU)
#define MPU_REGION_SIZE_128KB    ((uint8_t)0x10U)
#define MPU_REGION_SIZE_256KB    ((uint8_t)0x11U)
#define MPU_REGION_SIZE_512KB    ((uint8_t)0x12U)
#define MPU_REGION_SIZE_1MB      ((uint8_t)0x13U)
#define MPU_REGION_SIZE_2MB      ((uint8_t)0x14U)
#define MPU_REGION_SIZE_4MB      ((uint8_t)0x15U)
#define MPU_REGION_SIZE_8MB      ((uint8_t)0x16U)
#define MPU_REGION_SIZE_16MB     ((uint8_t)0x17U)
#define MPU_REGION_SIZE_32MB     ((uint8_t)0x18U)
#define MPU_REGION_SIZE_64MB     ((uint8_t)0x19U)
#define MPU_REGION_SIZE_128MB    ((uint8_t)0x1AU)
#define MPU_REGION_SIZE_256MB    ((uint8_t)0x1BU)
#define MPU_REGION_SIZE_512MB    ((uint8_t)0x1CU)
#define MPU_REGION_SIZE_1GB      ((uint8_t)0x1DU)
#define MPU_REGION_SIZE_2GB      ((uint8_t)0x1EU)
#define MPU_REGION_SIZE_4GB      ((uint8_t)0x1FU)

#define MPU_AP_NONE 0u 
#define MPU_AP_PRIV 1u
#define MPU_AP_URO  2u
#define MPU_AP_FULL 3u
#define MPU_AP_PRO  5u
#define MPU_AP_RO   6u

/** MPU Region Base Address Register Value
*
* \param Region The region to be configured, number 0 to 15.
* \param BaseAddress The base address for the region.
*/
#define MPU_RBAR(Region, BaseAddress) ((BaseAddress & MPU_RBAR_ADDR_Msk) | (Region & MPU_RBAR_REGION_Msk) | (1UL << MPU_RBAR_VALID_Pos))

/**
* MPU Region Attribut and Size Register Value
* 
* \param DisableExec       Instruction access disable bit, 1= disable instruction fetches.
* \param AccessPermission  Data access permissions, allows you to configure read/write access for User and Privileged mode.
* \param TypeExtField      Type extension field, allows you to configure memory access type, for example strongly ordered, peripheral.
* \param IsShareable       Region is shareable between multiple bus masters.
* \param IsCacheable       Region is cacheable, i.e. its value may be kept in cache.
* \param IsBufferable      Region is bufferable, i.e. using write-back caching. Cachable but non-bufferable regions use write-through policy.
* \param SubRegionDisable  Sub-region disable field.
* \param Size              Region size of the region be configured, for example 4K, 8K.
*/                         
#define MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable, SubRegionDisable, Size) \
    ((DisableExec      << MPU_RASR_XN_Pos)     & MPU_RASR_XN_Msk)     | \
    ((AccessPermission << MPU_RASR_AP_Pos)     & MPU_RASR_AP_Msk)     | \
    ((TypeExtField     << MPU_RASR_TEX_Pos)    & MPU_RASR_TEX_Msk)    | \
    ((IsShareable      << MPU_RASR_S_Pos)      & MPU_RASR_S_Msk)      | \
    ((IsCacheable      << MPU_RASR_C_Pos)      & MPU_RASR_C_Msk)      | \
    ((IsBufferable     << MPU_RASR_B_Pos)      & MPU_RASR_B_Msk)      | \
    ((SubRegionDisable << MPU_RASR_SRD_Pos)    & MPU_RASR_SRD_Msk)    | \
    ((Size             << MPU_RASR_SIZE_Pos)   & MPU_RASR_SIZE_Msk)   | \
    ((1UL              << MPU_RASR_ENABLE_Pos) & MPU_RASR_ENABLE_Msk)


/**
* Struct for a single MPU Region
*/
typedef struct _MPU_Region_t {
    uint32_t RBAR; //!< The region base address register value (RBAR)
    uint32_t RASR; //!< The region attribute and size register value (RASR) \ref MPU_RASR
} MPU_Region_t;
    
/** Enable the MPU.
* \param MPU_Control Default access permissions for unconfigured regions.
*/
__STATIC_INLINE void MPU_Enable(uint32_t MPU_Control)
{
    __DSB();
    __ISB();
    MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
}

/** Disable the MPU.
*/
__STATIC_INLINE void MPU_Disable()
{
    __DSB();
    __ISB();
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
    MPU->CTRL  &= ~MPU_CTRL_ENABLE_Msk;
}

/** Clear and disable the given MPU region.
* \param rnr Region number to be cleared.
*/
__STATIC_INLINE void MPU_ClrRegion(uint32_t rnr)
{
    MPU->RNR = rnr;
    MPU->RASR = 0u;
}

/** Configure an MPU region.
* \param rbar Value for RBAR register.
* \param rsar Value for RSAR register.
*/   
__STATIC_INLINE void MPU_SetRegion(uint32_t rbar, uint32_t rasr)
{
    MPU->RBAR = rbar;
    MPU->RASR = rasr;
}

/** Configure the given MPU region.
* \param rnr Region number to be configured.
* \param rbar Value for RBAR register.
* \param rsar Value for RSAR register.
*/   
__STATIC_INLINE void MPU_SetRegionEx(uint32_t rnr, uint32_t rbar, uint32_t rasr)
{
    MPU->RNR = rnr;
    MPU->RBAR = rbar;
    MPU->RASR = rasr;
}

/** Memcopy with strictly ordered memory access, e.g. for register targets.
* \param dst Destination data is copied to.
* \param src Source data is copied from.
* \param len Amount of data words to be copied.
*/
__STATIC_INLINE void orderedCpy(volatile uint32_t* dst, const uint32_t* restrict src, uint32_t len)
{
    for (uint32_t i = 0u; i < len; ++i) 
    {
        dst[i] = src[i];
    }
}

/** Load the given number of MPU regions from a table.
* \param table Pointer to the MPU configuration table.
* \param cnt Amount of regions to be configured.
*/
__STATIC_INLINE void MPU_Load(MPU_Region_t const* table, uint32_t cnt) 
{
    orderedCpy(&(MPU->RBAR), &(table->RBAR), cnt*sizeof(MPU_Region_t)/4u);
}

#endif
