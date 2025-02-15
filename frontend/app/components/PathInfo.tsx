"use client"

import * as React from "react"
import { Area, AreaChart, CartesianGrid, XAxis } from "recharts"

import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card"
import {
  ChartConfig,
  ChartContainer,
  ChartLegend,
  ChartLegendContent,
  ChartTooltip,
  ChartTooltipContent,
} from "@/components/ui/chart"
import { motionProfile } from "../motionProfile/motionProfile"
import { useAtom } from "jotai"
import { def_max_acc, pathsAtom, pathSelectAtom } from "../var"

const chartConfig = {
  Time: {
    label: "Time",
  },
  Velocity: {
    label: "Velocity",
    color: "hsl(var(--chart-2))",
  },
} satisfies ChartConfig

export default function PathInfo () {
  let [paths, ] = useAtom(pathsAtom)
  let [pathSelect, ] = useAtom(pathSelectAtom)
  let [acc, _] = useAtom(def_max_acc)

  let motionProfileResult = React.useMemo(() => {
    let points = paths[pathSelect]["points"]

    let nullData = {
      "total_time": 0,
      "total_dist": 0,
      "data": []
    }
    if (acc <= 0) return nullData
    for (let i = 0; i < points.length; i++) {
      if (!("maxSpeed" in points[i]) || points[i].maxSpeed <= 0) return nullData
    }

    let data = motionProfile(points, acc)
    return data
  }, [acc, paths, pathSelect])

  return (
    <>
      <Card>
        <CardHeader className="flex items-center gap-2 space-y-0 border-b py-5 sm:flex-row">
          <div className="grid flex-1 gap-1 text-center sm:text-left">
            <CardTitle>Motion Profile</CardTitle>
            <CardDescription>
              Velocity over Time
            </CardDescription>
          </div>
        </CardHeader>
        <CardContent className="px-2 pt-4 sm:px-6 sm:pt-6">
          <ChartContainer
            config={chartConfig}
            className="aspect-auto h-[250px] w-full"
          >
            <AreaChart data={motionProfileResult.data}>
              <defs>
                <linearGradient id="fillVelocity" x1="0" y1="0" x2="0" y2="1">
                  <stop
                    offset="5%"
                    stopColor="var(--color-Velocity)"
                    stopOpacity={0.8}
                  />
                  <stop
                    offset="95%"
                    stopColor="var(--color-Velocity)"
                    stopOpacity={0.1}
                  />
                </linearGradient>
              </defs>
              <CartesianGrid vertical={false} />
              <XAxis
                dataKey="Time"
                tickLine={true}
                axisLine={true}
                tickMargin={8}
                minTickGap={16}
                tickFormatter={(value) => {
                  return Math.round(value*10)/10 + " sec" 
                }}
              />
              <ChartTooltip
                cursor={false}
                content={
                  <ChartTooltipContent
                    labelFormatter={(value) => {
                      return "Velocity"
                    }}
                    indicator="dot"
                  />
                }
              />
              <Area
                dataKey="Velocity"
                type="linear"
                fill="url(#fillVelocity)"
                stroke="var(--color-Velocity)"
                stackId="a"
              />
              <ChartLegend content={<ChartLegendContent />} />
            </AreaChart>
          </ChartContainer>
        </CardContent>
      </Card>
      <p className="my-4">Total Distance: {Math.round(motionProfileResult.total_dist * 100) / 100} tiles</p>
      <p className="my-4">Total Time: {Math.round(motionProfileResult.total_time * 100) / 100} seconds</p>
    </>
  )
}

