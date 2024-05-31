/*
 * Copyright (c) 2024 Rapid Silicon
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "soc.h"

typedef struct {
    volatile uint32_t idrev;             /* 0x00 */
    volatile uint32_t reserved[10];      /* 0x04 - 0x28 */
    volatile uint32_t irq_map_mask[32];  /* 0x2C - 0xA8 */    
} scu_registers_t;

#if DT_HAS_COMPAT_STATUS_OKAY(rapidsi_scu)
    static volatile scu_registers_t *s_scu_regs = (scu_registers_t*)DT_REG_ADDR(DT_NODELABEL(scu));
#else
    #warning "Turn the rapidsi,scu status to okay in DTS else *s_scu_regs = NULL;"
    static volatile scu_registers_t *s_scu_regs = NULL;
#endif

void soc_get_id(uint8_t *chip_id, uint8_t *vendor_id)
{
    *chip_id = ((s_scu_regs->idrev & SOC_CHIP_ID_MASK) >> SOC_CHIP_ID_OFFSET);
    *vendor_id = ((s_scu_regs->idrev & SOC_VENDOR_ID_MASK) >> SOC_VENDOR_ID_OFFSET);
}

void soc_irq_map(enum map_mask_control_irq_id IRQn, uint8_t SubSystem)
{
    // Clearing Existing Value of the Mask
    s_scu_regs->irq_map_mask[IRQn+SOC_IRQ_CTRL_REG_OFFSET] &= ~(SOC_IRQ_MAP_MASK << SOC_IRQ_MAP_OFFSET);
    // Mapping to SubSystem
    s_scu_regs->irq_map_mask[IRQn+SOC_IRQ_CTRL_REG_OFFSET] |= (SubSystem << SOC_IRQ_MAP_OFFSET);
}

void soc_irq_unmap(enum map_mask_control_irq_id IRQn)
{
    s_scu_regs->irq_map_mask[IRQn+SOC_IRQ_CTRL_REG_OFFSET] &= ~(SOC_IRQ_MAP_MASK << SOC_IRQ_MAP_OFFSET);
}

void soc_irq_enable(enum map_mask_control_irq_id IRQn)
{
    s_scu_regs->irq_map_mask[IRQn+SOC_IRQ_CTRL_REG_OFFSET] |= SOC_IRQ_ENABLE;
}

void soc_irq_disable(enum map_mask_control_irq_id IRQn)
{
    s_scu_regs->irq_map_mask[IRQn+SOC_IRQ_CTRL_REG_OFFSET] &= ~(SOC_IRQ_ENABLE << SOC_IRQ_MASK_OFFSET);
}
